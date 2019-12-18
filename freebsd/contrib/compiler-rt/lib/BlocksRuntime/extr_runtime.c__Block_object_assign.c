#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int const BLOCK_BYREF_CALLER ; 
 int const BLOCK_FIELD_IS_BLOCK ; 
 int const BLOCK_FIELD_IS_BYREF ; 
 int const BLOCK_FIELD_IS_OBJECT ; 
 int const BLOCK_FIELD_IS_WEAK ; 
 int /*<<< orphan*/  _Block_assign (void*,void*) ; 
 int /*<<< orphan*/  _Block_assign_weak (void const*,void*) ; 
 int /*<<< orphan*/  _Block_byref_assign_copy (void*,void const*,int const) ; 
 void* _Block_copy_internal (void const*,int const) ; 
 int /*<<< orphan*/  _Block_retain_object (void const*) ; 

void _Block_object_assign(void *destAddr, const void *object, const int flags) {
    //printf("_Block_object_assign(*%p, %p, %x)\n", destAddr, object, flags);
    if ((flags & BLOCK_BYREF_CALLER) == BLOCK_BYREF_CALLER) {
        if ((flags & BLOCK_FIELD_IS_WEAK) == BLOCK_FIELD_IS_WEAK) {
            _Block_assign_weak(object, destAddr);
        }
        else {
            // do *not* retain or *copy* __block variables whatever they are
            _Block_assign((void *)object, destAddr);
        }
    }
    else if ((flags & BLOCK_FIELD_IS_BYREF) == BLOCK_FIELD_IS_BYREF)  {
        // copying a __block reference from the stack Block to the heap
        // flags will indicate if it holds a __weak reference and needs a special isa
        _Block_byref_assign_copy(destAddr, object, flags);
    }
    // (this test must be before next one)
    else if ((flags & BLOCK_FIELD_IS_BLOCK) == BLOCK_FIELD_IS_BLOCK) {
        // copying a Block declared variable from the stack Block to the heap
        _Block_assign(_Block_copy_internal(object, flags), destAddr);
    }
    // (this test must be after previous one)
    else if ((flags & BLOCK_FIELD_IS_OBJECT) == BLOCK_FIELD_IS_OBJECT) {
        //printf("retaining object at %p\n", object);
        _Block_retain_object(object);
        //printf("done retaining object at %p\n", object);
        _Block_assign((void *)object, destAddr);
    }
}