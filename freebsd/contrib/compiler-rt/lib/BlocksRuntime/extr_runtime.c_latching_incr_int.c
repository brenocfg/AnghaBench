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
 int BLOCK_REFCOUNT_MASK ; 
 scalar_t__ OSAtomicCompareAndSwapInt (int,int,int volatile*) ; 

__attribute__((used)) static int latching_incr_int(int *where) {
    while (1) {
        int old_value = *(volatile int *)where;
        if ((old_value & BLOCK_REFCOUNT_MASK) == BLOCK_REFCOUNT_MASK) {
            return BLOCK_REFCOUNT_MASK;
        }
        if (OSAtomicCompareAndSwapInt(old_value, old_value+1, (volatile int *)where)) {
            return old_value+1;
        }
    }
}