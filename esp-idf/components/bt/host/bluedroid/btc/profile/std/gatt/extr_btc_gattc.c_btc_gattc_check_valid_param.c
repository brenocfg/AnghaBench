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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  esp_gatt_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_GATT_INVALID_OFFSET ; 
 int /*<<< orphan*/  ESP_GATT_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_GATT_OK ; 

__attribute__((used)) static esp_gatt_status_t btc_gattc_check_valid_param(int num, uint16_t offset)
{
    if (num == 0) {
        return ESP_GATT_NOT_FOUND;
    } else if (offset >= num) {
        return ESP_GATT_INVALID_OFFSET;
    }

    return ESP_GATT_OK;
}