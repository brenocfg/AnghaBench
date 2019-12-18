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
typedef  size_t u16_t ;
struct bt_mesh_elem {size_t addr; } ;
struct TYPE_2__ {size_t elem_count; struct bt_mesh_elem* elem; } ;

/* Variables and functions */
 scalar_t__ BLE_MESH_ADDR_IS_UNICAST (size_t) ; 
 scalar_t__ bt_mesh_elem_find_group (struct bt_mesh_elem*,size_t) ; 
 TYPE_1__* dev_comp ; 

struct bt_mesh_elem *bt_mesh_elem_find(u16_t addr)
{
    u16_t index;

    if (BLE_MESH_ADDR_IS_UNICAST(addr)) {
        index = (addr - dev_comp->elem[0].addr);
        if (index < dev_comp->elem_count) {
            return &dev_comp->elem[index];
        } else {
            return NULL;
        }
    }

    for (index = 0; index < dev_comp->elem_count; index++) {
        struct bt_mesh_elem *elem = &dev_comp->elem[index];

        if (bt_mesh_elem_find_group(elem, addr)) {
            return elem;
        }
    }

    return NULL;
}