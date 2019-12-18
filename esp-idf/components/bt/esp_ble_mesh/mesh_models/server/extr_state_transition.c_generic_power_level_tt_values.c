#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
struct TYPE_4__ {float counter; } ;
struct bt_mesh_gen_power_level_srv {float tt_delta_level; TYPE_2__ transition; TYPE_1__* state; } ;
struct TYPE_3__ {scalar_t__ target_power_actual; scalar_t__ power_actual; } ;

/* Variables and functions */
 int /*<<< orphan*/  transition_time_values (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void generic_power_level_tt_values(struct bt_mesh_gen_power_level_srv *srv,
                                   u8_t trans_time, u8_t delay)
{
    transition_time_values(&srv->transition, trans_time, delay);
    srv->tt_delta_level =
        ((float) (srv->state->power_actual - srv->state->target_power_actual) / srv->transition.counter);
}