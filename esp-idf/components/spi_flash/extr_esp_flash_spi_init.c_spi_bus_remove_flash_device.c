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
struct TYPE_4__ {struct TYPE_4__* host; struct TYPE_4__* driver_data; } ;
typedef  TYPE_1__ esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

esp_err_t spi_bus_remove_flash_device(esp_flash_t *chip)
{
    if (chip==NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (chip->host) {
        free(chip->host->driver_data);
        free(chip->host);
    }
    free(chip);
    return ESP_OK;
}