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
 int light_client_init (struct bt_mesh_model*,int) ; 

int bt_mesh_light_lc_cli_init(struct bt_mesh_model *model, bool primary)
{
    return light_client_init(model, primary);
}