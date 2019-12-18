#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct bt_mesh_state_transition {int delay; TYPE_1__ timer; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_TRANS_TIMER_START ; 
 int /*<<< orphan*/  K_MSEC (int) ; 
 int /*<<< orphan*/  bt_mesh_atomic_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_delayed_work_submit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_work_submit (int /*<<< orphan*/ *) ; 

void bt_mesh_server_start_transition(struct bt_mesh_state_transition *transition)
{
    if (transition->delay) {
        k_delayed_work_submit(&transition->timer, K_MSEC(5 * transition->delay));
        bt_mesh_atomic_set_bit(transition->flag, BLE_MESH_TRANS_TIMER_START);
    } else {
        k_work_submit(&transition->timer.work);
    }
}