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
typedef  int /*<<< orphan*/  TIMER_LIST_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_THREAD_MAX_TIMEOUT ; 
 int /*<<< orphan*/  SIG_BTU_ONESHOT_ALARM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_timer_oneshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btu_task_post (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void btu_oneshot_alarm_cb(void *data)
{
    assert(data != NULL);
    TIMER_LIST_ENT *p_tle = (TIMER_LIST_ENT *)data;

    btu_stop_timer_oneshot(p_tle);

    btu_task_post(SIG_BTU_ONESHOT_ALARM, p_tle, OSI_THREAD_MAX_TIMEOUT);
}