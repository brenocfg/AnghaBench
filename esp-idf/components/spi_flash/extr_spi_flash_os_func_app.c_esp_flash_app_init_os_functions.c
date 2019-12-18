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
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  esp_flash_spi1_default_os_functions ; 
 int /*<<< orphan*/  main_flash_arg ; 

esp_err_t esp_flash_app_init_os_functions(esp_flash_t* chip)
{
    chip->os_func = &esp_flash_spi1_default_os_functions;
    chip->os_func_data = &main_flash_arg;
    return ESP_OK;
}