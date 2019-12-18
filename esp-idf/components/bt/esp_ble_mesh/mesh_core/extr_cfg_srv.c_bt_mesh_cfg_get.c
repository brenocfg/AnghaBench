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
struct bt_mesh_cfg_srv {int dummy; } ;

/* Variables and functions */
 struct bt_mesh_cfg_srv* conf ; 

struct bt_mesh_cfg_srv *bt_mesh_cfg_get(void)
{
    return conf;
}