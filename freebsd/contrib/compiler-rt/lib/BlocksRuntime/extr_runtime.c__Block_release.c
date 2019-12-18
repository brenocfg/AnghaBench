#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Block_layout {int flags; TYPE_1__* descriptor; } ;
typedef  int int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* dispose ) (struct Block_layout*) ;} ;

/* Variables and functions */
 int BLOCK_HAS_COPY_DISPOSE ; 
 int BLOCK_IS_GC ; 
 int BLOCK_IS_GLOBAL ; 
 int BLOCK_NEEDS_FREE ; 
 int BLOCK_REFCOUNT_MASK ; 
 int /*<<< orphan*/  _Block_deallocator (struct Block_layout*) ; 
 int /*<<< orphan*/  _Block_setHasRefcount (struct Block_layout*,int) ; 
 int latching_decr_int (int*) ; 
 int /*<<< orphan*/  printf (char*,void*) ; 
 int /*<<< orphan*/  stub1 (struct Block_layout*) ; 

void _Block_release(void *arg) {
    struct Block_layout *aBlock = (struct Block_layout *)arg;
    int32_t newCount;
    if (!aBlock) return;
    newCount = latching_decr_int(&aBlock->flags) & BLOCK_REFCOUNT_MASK;
    if (newCount > 0) return;
    // Hit zero
    if (aBlock->flags & BLOCK_IS_GC) {
        // Tell GC we no longer have our own refcounts.  GC will decr its refcount
        // and unless someone has done a CFRetain or marked it uncollectable it will
        // now be subject to GC reclamation.
        _Block_setHasRefcount(aBlock, false);
    }
    else if (aBlock->flags & BLOCK_NEEDS_FREE) {
        if (aBlock->flags & BLOCK_HAS_COPY_DISPOSE)(*aBlock->descriptor->dispose)(aBlock);
        _Block_deallocator(aBlock);
    }
    else if (aBlock->flags & BLOCK_IS_GLOBAL) {
        ;
    }
    else {
        printf("Block_release called upon a stack Block: %p, ignored\n", (void *)aBlock);
    }
}