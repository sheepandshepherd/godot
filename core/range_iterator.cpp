/*************************************************************************/
/*  range_iterator.cpp                                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2016 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "range_iterator.h"
#include "core_string_names.h"
#include "object_type_db.h"

void RangeIterator::_bind_methods() {
	ObjectTypeDB::bind_method(_MD("_iter_init","arg"),&RangeIterator::_iter_init);
	ObjectTypeDB::bind_method(_MD("_iter_next","arg"),&RangeIterator::_iter_next);
	ObjectTypeDB::bind_method(_MD("_iter_get","arg"),&RangeIterator::_iter_get);
	ObjectTypeDB::bind_method(_MD("isFinished"),&RangeIterator::is_finished);
	ObjectTypeDB::bind_method(_MD("set_range","arg1","arg2","arg3"),&RangeIterator::set_range,DEFVAL(Variant()),DEFVAL(Variant()));
}

bool RangeIterator::_iter_init(Variant arg) {
	return !is_finished();
}

bool RangeIterator::_iter_next(Variant arg) {
	current += step;
	return !is_finished();
}

Variant RangeIterator::_iter_get(Variant arg) {
	return Variant(current);
}

bool RangeIterator::is_finished() {
	if(step > 0)
	{
		return current >= stop;
	}
	else
	{
		return current <= stop;
	}
}

void RangeIterator::_set_range(int stop) {
	this->current = 0;
	this->stop = stop;
	this->step = (stop > 0)?(1):(-1);
}

void RangeIterator::_set_range(int start, int stop) {
	this->current = start;
	this->stop = stop;
	this->step = (stop > start)?(1):(-1);
}

void RangeIterator::_set_range(int start, int stop, int step) {
	this->current = start;
	this->stop = stop;
	this->step = step;
}

Ref<RangeIterator> RangeIterator::set_range(Variant arg1, Variant arg2, Variant arg3)
{
	if(arg2.get_type() == Variant::NIL)
	{
		_set_range((int)arg1); // (end)
	}
	else
	{
		if(arg3.get_type() == Variant::NIL) _set_range((int)arg1, (int)arg2); // (start, end)
		else _set_range((int)arg1, (int)arg2, (int)arg3); // (start, end, step)
	}
	return Ref<RangeIterator>(this);
}






