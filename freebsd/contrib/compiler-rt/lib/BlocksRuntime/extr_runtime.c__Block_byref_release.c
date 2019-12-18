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
struct Block_layout {int dummy; } ;
struct Block_byref {int flags; int /*<<< orphan*/  (* byref_destroy ) (struct Block_byref*) ;struct Block_byref* forwarding; } ;

/* Variables and functions */
 int BLOCK_HAS_COPY_DISPOSE ; 
 int BLOCK_NEEDS_FREE ; 
 int BLOCK_REFCOUNT_MASK ; 
 int /*<<< orphan*/  _Block_deallocator (struct Block_layout*) ; 
 int latching_decr_int (int*) ; 
 int /*<<< orphan*/  printf (char*,void const*) ; 
 int /*<<< orphan*/  stub1 (struct Block_byref*) ; 

__attribute__((used)) static void _Block_byref_release(const void *arg) {
    struct Block_byref *shared_struct = (struct Block_byref *)arg;
    int refcount;

    // dereference the forwarding pointer since the compiler isn't doing this anymore (ever?)
    shared_struct = shared_struct->forwarding;
    
    //printf("_Block_byref_release %p called, flags are %x\n", shared_struct, shared_struct->flags);
    // To support C++ destructors under GC we arrange for there to be a finalizer for this
    // by using an isa that directs the code to a finalizer that calls the byref_destroy method.
    if ((shared_struct->flags & BLOCK_NEEDS_FREE) == 0) {
        return; // stack or GC or global
    }
    refcount = shared_struct->flags & BLOCK_REFCOUNT_MASK;
    if (refcount <= 0) {
        printf("_Block_byref_release: Block byref data structure at %p underflowed\n", arg);
    }
    else if ((latching_decr_int(&shared_struct->flags) & BLOCK_REFCOUNT_MASK) == 0) {
        //printf("disposing of heap based byref block\n");
        if (shared_struct->flags & BLOCK_HAS_COPY_DISPOSE) {
            //printf("calling out to helper\n");
            (*shared_struct->byref_destroy)(shared_struct);
        }
        _Block_deallocator((struct Block_layout *)shared_struct);
    }
}