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
typedef  size_t hv_trap_type_t ;
struct TYPE_3__ {int /*<<< orphan*/ * traps; scalar_t__ trap_count; } ;
typedef  TYPE_1__ hv_trap_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSMemoryBarrier () ; 
 int /*<<< orphan*/  hv_support_lck_mtx ; 
 TYPE_1__* hv_trap_table ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

void
hv_release_traps(hv_trap_type_t trap_type) {
	hv_trap_table_t *trap_table = &hv_trap_table[trap_type];

	lck_mtx_lock(hv_support_lck_mtx);
	trap_table->trap_count = 0;
	OSMemoryBarrier();
	trap_table->traps = NULL;
	lck_mtx_unlock(hv_support_lck_mtx);
}