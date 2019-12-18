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
struct Block_layout {int flags; } ;

/* Variables and functions */
 int BLOCK_IS_GC ; 
 int /*<<< orphan*/  _Block_release (struct Block_layout*) ; 

__attribute__((used)) static void _Block_destroy(const void *arg) {
    struct Block_layout *aBlock;
    if (!arg) return;
    aBlock = (struct Block_layout *)arg;
    if (aBlock->flags & BLOCK_IS_GC) {
        // assert(aBlock->Block_flags & BLOCK_HAS_CTOR);
        return; // ignore, we are being called because of a DTOR
    }
    _Block_release(aBlock);
}