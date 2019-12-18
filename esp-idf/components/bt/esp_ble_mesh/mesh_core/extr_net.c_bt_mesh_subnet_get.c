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
typedef  scalar_t__ u16_t ;
struct bt_mesh_subnet {scalar_t__ net_idx; } ;
struct TYPE_2__ {struct bt_mesh_subnet* sub; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bt_mesh_subnet*) ; 
 scalar_t__ BLE_MESH_KEY_ANY ; 
 TYPE_1__ bt_mesh ; 

struct bt_mesh_subnet *bt_mesh_subnet_get(u16_t net_idx)
{
    int i;

    if (net_idx == BLE_MESH_KEY_ANY) {
        return &bt_mesh.sub[0];
    }

    for (i = 0; i < ARRAY_SIZE(bt_mesh.sub); i++) {
        if (bt_mesh.sub[i].net_idx == net_idx) {
            return &bt_mesh.sub[i];
        }
    }

    return NULL;
}