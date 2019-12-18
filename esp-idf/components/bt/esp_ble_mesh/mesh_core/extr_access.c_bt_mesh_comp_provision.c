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
typedef  int /*<<< orphan*/  u16_t ;
struct bt_mesh_elem {int /*<<< orphan*/  vnd_model_count; int /*<<< orphan*/  model_count; scalar_t__ addr; } ;
struct TYPE_2__ {int elem_count; struct bt_mesh_elem* elem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,scalar_t__,int,...) ; 
 TYPE_1__* dev_comp ; 
 int /*<<< orphan*/  dev_primary_addr ; 

void bt_mesh_comp_provision(u16_t addr)
{
    int i;

    dev_primary_addr = addr;

    BT_DBG("addr 0x%04x elem_count %u", addr, dev_comp->elem_count);

    for (i = 0; i < dev_comp->elem_count; i++) {
        struct bt_mesh_elem *elem = &dev_comp->elem[i];

        elem->addr = addr++;

        BT_DBG("addr 0x%04x mod_count %u vnd_mod_count %u",
               elem->addr, elem->model_count, elem->vnd_model_count);
    }
}