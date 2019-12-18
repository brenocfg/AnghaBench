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
struct bt_mesh_state_transition {int /*<<< orphan*/  flag; int /*<<< orphan*/  quo_tt; int /*<<< orphan*/  timer; int /*<<< orphan*/  start_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_TRANS_TIMER_START ; 
 int /*<<< orphan*/  K_MSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_atomic_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_delayed_work_submit_periodic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_uptime_get () ; 

__attribute__((used)) static void transition_timer_start(struct bt_mesh_state_transition *transition)
{
    transition->start_timestamp = k_uptime_get();
    k_delayed_work_submit_periodic(&transition->timer, K_MSEC(transition->quo_tt));
    bt_mesh_atomic_set_bit(transition->flag, BLE_MESH_TRANS_TIMER_START);
}