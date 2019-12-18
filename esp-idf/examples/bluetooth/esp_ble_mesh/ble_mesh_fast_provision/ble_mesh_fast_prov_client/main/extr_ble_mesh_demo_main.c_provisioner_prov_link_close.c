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
typedef  scalar_t__ esp_ble_mesh_prov_bearer_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_node_num; } ;

/* Variables and functions */
 scalar_t__ ESP_BLE_MESH_PROV_ADV ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__ prov_info ; 

__attribute__((used)) static void provisioner_prov_link_close(esp_ble_mesh_prov_bearer_t bearer, uint8_t reason)
{
    ESP_LOGI(TAG, "%s link close, reason 0x%02x",
             bearer == ESP_BLE_MESH_PROV_ADV ? "PB-ADV" : "PB-GATT", reason);

    if (bearer == ESP_BLE_MESH_PROV_ADV && reason != 0x00) {
        prov_info.max_node_num++;
    }
}