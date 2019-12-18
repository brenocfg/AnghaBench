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
struct bt_mesh_model {int dummy; } ;

/* Variables and functions */
 int light_server_init (struct bt_mesh_model*) ; 

int bt_mesh_light_xyl_setup_srv_init(struct bt_mesh_model *model, bool primary)
{
    return light_server_init(model);
}