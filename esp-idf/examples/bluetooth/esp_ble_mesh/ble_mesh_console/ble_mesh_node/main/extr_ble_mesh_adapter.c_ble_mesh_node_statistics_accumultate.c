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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_2__ {size_t total_package_num; size_t* package_index; int package_num; int /*<<< orphan*/  statistics; } ;

/* Variables and functions */
 int /*<<< orphan*/  ble_mesh_node_sema ; 
 TYPE_1__ ble_mesh_node_statistics ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ble_mesh_node_statistics_accumultate(uint8_t *data, uint32_t value, uint16_t type)
{
    uint16_t i;
    uint16_t sequence_num = (data[0] << 8) | data[1];

    xSemaphoreTake(ble_mesh_node_sema, portMAX_DELAY);
    for (i = 0; i < ble_mesh_node_statistics.total_package_num; i++) {
        if (ble_mesh_node_statistics.package_index[i] == sequence_num) {
            xSemaphoreGive(ble_mesh_node_sema);
            return 1;
        }
    }

    // package type wrong
    if (data[2] != type) {
        xSemaphoreGive(ble_mesh_node_sema);
        return 1;
    }

    for (i = 0; i < ble_mesh_node_statistics.total_package_num; i++) {
        if (ble_mesh_node_statistics.package_index[i] == 0) {
            ble_mesh_node_statistics.package_index[i] = sequence_num;
            ble_mesh_node_statistics.package_num += 1;
            ble_mesh_node_statistics.statistics += value;
            break;
        }
    }
    xSemaphoreGive(ble_mesh_node_sema);
    return 0;
}