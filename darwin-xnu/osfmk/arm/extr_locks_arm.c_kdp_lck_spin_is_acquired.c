#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int lck_spin_data; } ;
typedef  TYPE_1__ lck_spin_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LCK_SPIN_TAG_DESTROYED ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ not_in_kdp ; 
 int /*<<< orphan*/  panic (char*) ; 

boolean_t
kdp_lck_spin_is_acquired(lck_spin_t *lck) {
	if (not_in_kdp) {
		panic("panic: spinlock acquired check done outside of kernel debugger");
	}
	return ((lck->lck_spin_data & ~LCK_SPIN_TAG_DESTROYED) != 0) ? TRUE:FALSE;
}