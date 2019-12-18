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
 int /*<<< orphan*/  dt_xc_lock ; 
 int /*<<< orphan*/  dtrace_lck_attr ; 
 int /*<<< orphan*/  dtrace_lck_grp ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dtrace_isa_init(void)
{
#if __ARM_SMP__
	lck_mtx_init(&dt_xc_lock, dtrace_lck_grp, dtrace_lck_attr);
#endif
	return;
}