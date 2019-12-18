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
struct bt_mesh_hb_pub {int dummy; } ;
struct TYPE_2__ {struct bt_mesh_hb_pub hb_pub; } ;

/* Variables and functions */
 TYPE_1__* conf ; 

struct bt_mesh_hb_pub *bt_mesh_hb_pub_get(void)
{
    if (!conf) {
        return NULL;
    }

    return &conf->hb_pub;
}