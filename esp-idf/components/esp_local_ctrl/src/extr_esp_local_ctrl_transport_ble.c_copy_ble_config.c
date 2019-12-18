#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  protocomm_ble_name_uuid_t ;
typedef  int /*<<< orphan*/  protocomm_ble_config_t ;
struct TYPE_7__ {TYPE_3__* ble; } ;
typedef  TYPE_2__ esp_local_ctrl_transport_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {int nu_lookup_count; TYPE_1__* nu_lookup; int /*<<< orphan*/  service_uuid; int /*<<< orphan*/  device_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t copy_ble_config(esp_local_ctrl_transport_config_t *dest_config, const esp_local_ctrl_transport_config_t *src_config)
{
    if (!dest_config || !src_config || !src_config->ble) {
        ESP_LOGE(TAG, "NULL arguments provided");
        return ESP_ERR_INVALID_ARG;
    }

    dest_config->ble = calloc(1, sizeof(protocomm_ble_config_t));
    if (!dest_config->ble) {
        ESP_LOGE(TAG, "Failed to allocate memory for BLE transport config");
        return ESP_ERR_NO_MEM;
    }

    /* Copy BLE device name */
    memcpy(dest_config->ble->device_name,
           src_config->ble->device_name,
           sizeof(src_config->ble->device_name));

    /* Copy Service UUID */
    memcpy(dest_config->ble->service_uuid,
           src_config->ble->service_uuid,
           sizeof(src_config->ble->service_uuid));

    dest_config->ble->nu_lookup_count = 0;
    if (src_config->ble->nu_lookup_count) {
        /* Copy any provided name-uuid lookup table */
        dest_config->ble->nu_lookup = calloc(src_config->ble->nu_lookup_count,
                                             sizeof(protocomm_ble_name_uuid_t));
        if (!dest_config->ble->nu_lookup) {
            ESP_LOGE(TAG, "Failed to allocate memory for BLE characteristic names");
            free(dest_config->ble);
            return ESP_ERR_NO_MEM;
        }
        for (uint16_t i = 0; i < src_config->ble->nu_lookup_count; i++) {
            dest_config->ble->nu_lookup[i].uuid = src_config->ble->nu_lookup[i].uuid;
            if (!src_config->ble->nu_lookup[i].name) {
                ESP_LOGE(TAG, "Endpoint name cannot be null");
                return ESP_ERR_INVALID_ARG;
            }
            dest_config->ble->nu_lookup[i].name = strdup(src_config->ble->nu_lookup[i].name);
            if (!dest_config->ble->nu_lookup[i].name) {
                ESP_LOGE(TAG, "Failed to allocate memory for endpoint name");
                return ESP_ERR_NO_MEM;
            }
            dest_config->ble->nu_lookup_count++;
        }
    }
    return ESP_OK;
}