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
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_call_init_abstime () ; 
 int /*<<< orphan*/  timer_call_lck_attr ; 
 int /*<<< orphan*/  timer_call_lck_grp ; 
 int /*<<< orphan*/  timer_call_lck_grp_attr ; 
 int /*<<< orphan*/  timer_longterm_init () ; 

void
timer_call_init(void)
{
	lck_attr_setdefault(&timer_call_lck_attr);
	lck_grp_attr_setdefault(&timer_call_lck_grp_attr);
	lck_grp_init(&timer_call_lck_grp, "timer_call", &timer_call_lck_grp_attr);

	timer_longterm_init();
	timer_call_init_abstime();
}