#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * os_func_data; int /*<<< orphan*/ * os_func; } ;
typedef  TYPE_1__ esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  esp_flash_spi1_default_os_functions ; 
 int /*<<< orphan*/  esp_flash_spi23_default_os_functions ; 
 int /*<<< orphan*/  spi1_arg ; 
 int /*<<< orphan*/  spi2_arg ; 
 int /*<<< orphan*/  spi3_arg ; 

esp_err_t esp_flash_init_os_functions(esp_flash_t *chip, int host_id)
{
    if (host_id == 0) {
        //SPI1
        chip->os_func = &esp_flash_spi1_default_os_functions;
        chip->os_func_data = &spi1_arg;
    } else if (host_id == 1 || host_id == 2) {
        //SPI2,3
        chip->os_func = &esp_flash_spi23_default_os_functions;
        chip->os_func_data = (host_id == 1) ? &spi2_arg : &spi3_arg;
    } else {
        return ESP_ERR_INVALID_ARG;
    }
    return ESP_OK;
}