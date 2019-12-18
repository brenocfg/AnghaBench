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
struct bt_mesh_light_ctl_temp_srv {float tt_delta_temperature; float tt_delta_delta_uv; TYPE_2__ transition; TYPE_1__* state; } ;
struct TYPE_3__ {scalar_t__ target_delta_uv; scalar_t__ delta_uv; scalar_t__ target_temperature; scalar_t__ temperature; } ;

/* Variables and functions */
 int /*<<< orphan*/  transition_time_values (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void light_ctl_temp_tt_values(struct bt_mesh_light_ctl_temp_srv *srv,
                              u8_t trans_time, u8_t delay)
{
    transition_time_values(&srv->transition, trans_time, delay);
    srv->tt_delta_temperature =
        ((float) (srv->state->temperature - srv->state->target_temperature) / srv->transition.counter);
    srv->tt_delta_delta_uv =
        ((float) (srv->state->delta_uv - srv->state->target_delta_uv) / srv->transition.counter);
}