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
struct bt_mesh_state_transition {int /*<<< orphan*/  flag; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_TRANS_TIMER_START ; 
 int /*<<< orphan*/  bt_mesh_atomic_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_delayed_work_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void transition_timer_stop(struct bt_mesh_state_transition *transition)
{
    k_delayed_work_cancel(&transition->timer);
    bt_mesh_atomic_clear_bit(transition->flag, BLE_MESH_TRANS_TIMER_START);
}