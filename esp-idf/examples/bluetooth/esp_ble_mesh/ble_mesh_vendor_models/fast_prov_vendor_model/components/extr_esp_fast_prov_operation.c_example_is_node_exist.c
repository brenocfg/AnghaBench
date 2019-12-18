#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  unicast_addr; } ;
typedef  TYPE_1__ example_node_info_t ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ ESP_BLE_MESH_ADDR_IS_UNICAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 TYPE_1__* nodes_info ; 

bool example_is_node_exist(const uint8_t uuid[16])
{
    example_node_info_t *node = NULL;

    if (!uuid) {
        return false;
    }

    for (int i = 0; i < ARRAY_SIZE(nodes_info); i++) {
        node = &nodes_info[i];
        if (ESP_BLE_MESH_ADDR_IS_UNICAST(node->unicast_addr)) {
            if (!memcmp(node->uuid, uuid, 16)) {
                return true;
            }
        }
    }

    return false;
}