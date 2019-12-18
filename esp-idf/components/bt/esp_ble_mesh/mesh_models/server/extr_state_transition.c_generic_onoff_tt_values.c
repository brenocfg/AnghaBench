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
typedef  int /*<<< orphan*/  u8_t ;
struct bt_mesh_gen_onoff_srv {int /*<<< orphan*/  transition; } ;

/* Variables and functions */
 void transition_time_values (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void generic_onoff_tt_values(struct bt_mesh_gen_onoff_srv *srv,
                             u8_t trans_time, u8_t delay)
{
    return transition_time_values(&srv->transition, trans_time, delay);
}