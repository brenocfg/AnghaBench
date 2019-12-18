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
typedef  int /*<<< orphan*/  data_free_fn ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_GENERAL_ALARM_HASH_MAP_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bm_alarm_hash_map ; 
 int /*<<< orphan*/  bm_alarm_lock ; 
 int /*<<< orphan*/  bm_irq_lock ; 
 int /*<<< orphan*/  hash_function_pointer ; 
 int /*<<< orphan*/ * hash_map_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ osi_alarm_free ; 
 int /*<<< orphan*/  osi_mutex_new (int /*<<< orphan*/ *) ; 

void bt_mesh_k_init(void)
{
    osi_mutex_new(&bm_alarm_lock);
    osi_mutex_new(&bm_irq_lock);
    bm_alarm_hash_map = hash_map_new(BLE_MESH_GENERAL_ALARM_HASH_MAP_SIZE,
                                     hash_function_pointer, NULL,
                                     (data_free_fn)osi_alarm_free, NULL);
    assert(bm_alarm_hash_map != NULL);
}