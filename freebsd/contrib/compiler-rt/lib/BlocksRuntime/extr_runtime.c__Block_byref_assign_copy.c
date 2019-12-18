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
struct Block_byref_header {int dummy; } ;
struct Block_byref {int flags; struct Block_byref* forwarding; scalar_t__ size; int /*<<< orphan*/  (* byref_keep ) (struct Block_byref*,struct Block_byref*) ;int /*<<< orphan*/  byref_destroy; int /*<<< orphan*/ * isa; } ;

/* Variables and functions */
 int const BLOCK_FIELD_IS_BYREF ; 
 int const BLOCK_FIELD_IS_WEAK ; 
 int BLOCK_HAS_COPY_DISPOSE ; 
 int BLOCK_IS_GC ; 
 int BLOCK_NEEDS_FREE ; 
 int BLOCK_REFCOUNT_MASK ; 
 scalar_t__ _Block_allocator (scalar_t__,int,int) ; 
 int /*<<< orphan*/  _Block_assign (struct Block_byref*,void**) ; 
 int /*<<< orphan*/  _Block_memmove (void*,void*,scalar_t__) ; 
 int _Byref_flag_initial_value ; 
 int /*<<< orphan*/  _NSConcreteWeakBlockVariable ; 
 int /*<<< orphan*/  latching_incr_int (int*) ; 
 int /*<<< orphan*/  stub1 (struct Block_byref*,struct Block_byref*) ; 

__attribute__((used)) static void _Block_byref_assign_copy(void *dest, const void *arg, const int flags) {
    struct Block_byref **destp = (struct Block_byref **)dest;
    struct Block_byref *src = (struct Block_byref *)arg;
        
    //printf("_Block_byref_assign_copy called, byref destp %p, src %p, flags %x\n", destp, src, flags);
    //printf("src dump: %s\n", _Block_byref_dump(src));
    if (src->forwarding->flags & BLOCK_IS_GC) {
        ;   // don't need to do any more work
    }
    else if ((src->forwarding->flags & BLOCK_REFCOUNT_MASK) == 0) {
        //printf("making copy\n");
        // src points to stack
        bool isWeak = ((flags & (BLOCK_FIELD_IS_BYREF|BLOCK_FIELD_IS_WEAK)) == (BLOCK_FIELD_IS_BYREF|BLOCK_FIELD_IS_WEAK));
        // if its weak ask for an object (only matters under GC)
        struct Block_byref *copy = (struct Block_byref *)_Block_allocator(src->size, false, isWeak);
        copy->flags = src->flags | _Byref_flag_initial_value; // non-GC one for caller, one for stack
        copy->forwarding = copy; // patch heap copy to point to itself (skip write-barrier)
        src->forwarding = copy;  // patch stack to point to heap copy
        copy->size = src->size;
        if (isWeak) {
            copy->isa = &_NSConcreteWeakBlockVariable;  // mark isa field so it gets weak scanning
        }
        if (src->flags & BLOCK_HAS_COPY_DISPOSE) {
            // Trust copy helper to copy everything of interest
            // If more than one field shows up in a byref block this is wrong XXX
            copy->byref_keep = src->byref_keep;
            copy->byref_destroy = src->byref_destroy;
            (*src->byref_keep)(copy, src);
        }
        else {
            // just bits.  Blast 'em using _Block_memmove in case they're __strong
            _Block_memmove(
                (void *)&copy->byref_keep,
                (void *)&src->byref_keep,
                src->size - sizeof(struct Block_byref_header));
        }
    }
    // already copied to heap
    else if ((src->forwarding->flags & BLOCK_NEEDS_FREE) == BLOCK_NEEDS_FREE) {
        latching_incr_int(&src->forwarding->flags);
    }
    // assign byref data block pointer into new Block
    _Block_assign(src->forwarding, (void **)destp);
}