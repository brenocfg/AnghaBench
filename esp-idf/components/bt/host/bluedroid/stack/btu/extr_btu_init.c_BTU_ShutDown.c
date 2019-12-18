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
 int /*<<< orphan*/  FREE_AND_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_cb_ptr ; 
 int /*<<< orphan*/ * btu_general_alarm_hash_map ; 
 int /*<<< orphan*/  btu_general_alarm_lock ; 
 int /*<<< orphan*/ * btu_l2cap_alarm_hash_map ; 
 int /*<<< orphan*/  btu_l2cap_alarm_lock ; 
 int /*<<< orphan*/ * btu_oneshot_alarm_hash_map ; 
 int /*<<< orphan*/  btu_oneshot_alarm_lock ; 
 int /*<<< orphan*/  btu_task_shut_down () ; 
 int /*<<< orphan*/ * btu_thread ; 
 int /*<<< orphan*/  hash_map_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_mutex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_thread_free (int /*<<< orphan*/ *) ; 

void BTU_ShutDown(void)
{
#if BTU_DYNAMIC_MEMORY
    FREE_AND_RESET(btu_cb_ptr);
#endif
    btu_task_shut_down();

    hash_map_free(btu_general_alarm_hash_map);
    osi_mutex_free(&btu_general_alarm_lock);

    hash_map_free(btu_oneshot_alarm_hash_map);
    osi_mutex_free(&btu_oneshot_alarm_lock);

    hash_map_free(btu_l2cap_alarm_hash_map);
    osi_mutex_free(&btu_l2cap_alarm_lock);

    if (btu_thread) {
        osi_thread_free(btu_thread);
        btu_thread = NULL;
    }

    btu_general_alarm_hash_map = NULL;
    btu_oneshot_alarm_hash_map = NULL;
    btu_l2cap_alarm_hash_map = NULL;
}