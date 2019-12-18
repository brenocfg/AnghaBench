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
typedef  int /*<<< orphan*/  period_ms_t ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  TIMER_LIST_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 int /*<<< orphan*/  bta_alarm_hash_map ; 
 int /*<<< orphan*/  bta_alarm_lock ; 
 int /*<<< orphan*/  hash_iter_ro_cb ; 
 int /*<<< orphan*/  hash_map_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 

UINT32 bta_sys_get_remaining_ticks(TIMER_LIST_ENT *p_target_tle)
{
    period_ms_t remaining_ms = 0;
    osi_mutex_lock(&bta_alarm_lock, OSI_MUTEX_MAX_TIMEOUT);
    // Get the alarm for this p_tle
    hash_map_foreach(bta_alarm_hash_map, hash_iter_ro_cb, &remaining_ms);
    osi_mutex_unlock(&bta_alarm_lock);
    return remaining_ms;
}