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
 int /*<<< orphan*/  bta_alarm_hash_map ; 
 int /*<<< orphan*/  bta_alarm_lock ; 
 int /*<<< orphan*/  bta_sys_cb_ptr ; 
 int /*<<< orphan*/  hash_map_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_free (int /*<<< orphan*/ *) ; 

void bta_sys_free(void)
{
    hash_map_free(bta_alarm_hash_map);
    osi_mutex_free(&bta_alarm_lock);
#if BTA_DYNAMIC_MEMORY
    FREE_AND_RESET(bta_sys_cb_ptr);
#endif
}