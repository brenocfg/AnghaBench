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
typedef  size_t u8_t ;
typedef  int u16_t ;
struct bt_mesh_scheduler_state {size_t schedule_count; TYPE_1__* schedules; } ;
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */

__attribute__((used)) static u16_t get_schedule_reg_bit(struct bt_mesh_scheduler_state *state)
{
    u16_t val = 0;
    u8_t i;

    for (i = 0U; i < state->schedule_count; i++) {
        if (state->schedules[i].in_use) {
            val |= (1 << i);
        }
    }

    return val;
}