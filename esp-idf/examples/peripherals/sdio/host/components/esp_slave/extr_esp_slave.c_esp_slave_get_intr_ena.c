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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  esp_slave_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  HOST_SLC0HOST_INT_ENA_REG ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_slave_read_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

esp_err_t esp_slave_get_intr_ena(esp_slave_context_t *context, uint32_t *ena_mask_o)
{
    ESP_LOGV(TAG, "get_intr_ena");
    esp_err_t ret = esp_slave_read_bytes(context, HOST_SLC0HOST_INT_ENA_REG, (uint8_t*)ena_mask_o, 4);
    ESP_LOGV(TAG, "ena: %08X", *ena_mask_o);
    return ret;
}