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
typedef  size_t uint16_t ;
struct TYPE_2__ {int net_idx; int unicast_addr; } ;

/* Variables and functions */
 size_t NODE_MAX_GROUP_CONFIG ; 
 TYPE_1__* ble_mesh_node_prestore_params ; 
 int /*<<< orphan*/  ble_mesh_node_sema ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ble_mesh_set_node_prestore_params(uint16_t netkey_index, uint16_t unicast_addr)
{
    uint16_t i;
    xSemaphoreTake(ble_mesh_node_sema, portMAX_DELAY);
    for (i = 0; i < NODE_MAX_GROUP_CONFIG; i++) {
        if (ble_mesh_node_prestore_params[i].net_idx != 0xFFFF && ble_mesh_node_prestore_params[i].unicast_addr != 0xFFFF) {
            ble_mesh_node_prestore_params[i].net_idx = netkey_index;
            ble_mesh_node_prestore_params[i].unicast_addr = unicast_addr;
        }
    }
    xSemaphoreGive(ble_mesh_node_sema);
}