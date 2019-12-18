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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  HOST_SLC0HOST_INT_RAW_REG ; 
 int /*<<< orphan*/  HOST_SLC0HOST_INT_ST_REG ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_slave_read_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

esp_err_t esp_slave_get_intr(esp_slave_context_t *context, uint32_t *intr_raw, uint32_t *intr_st)
{
    esp_err_t r;
    ESP_LOGV(TAG, "get_intr");
    if (intr_raw == NULL && intr_st == NULL) return ESP_ERR_INVALID_ARG;

    if (intr_raw != NULL) {
        r= esp_slave_read_bytes(context, HOST_SLC0HOST_INT_RAW_REG, (uint8_t*)intr_raw, 4);
        if (r != ESP_OK) return r;
    }
    if (intr_st != NULL) {
        r = esp_slave_read_bytes(context, HOST_SLC0HOST_INT_ST_REG, (uint8_t*)intr_st, 4);
        if (r != ESP_OK) return r;
    }
    return ESP_OK;
}