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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (scalar_t__) ; 
 scalar_t__ ESP_ERR_NVS_NEW_VERSION_FOUND ; 
 scalar_t__ ESP_ERR_NVS_NO_FREE_PAGES ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  GPIO_MODE_DEF_INPUT ; 
 int /*<<< orphan*/  GPIO_NUM_0 ; 
 char* esp_err_to_name (scalar_t__) ; 
 int /*<<< orphan*/  esp_restart () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_get_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_pad_select_gpio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_direction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_flash_erase () ; 
 scalar_t__ nvs_flash_init () ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ print_what_saved () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ save_restart_counter () ; 
 scalar_t__ save_run_time () ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void app_main(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

    err = print_what_saved();
    if (err != ESP_OK) printf("Error (%s) reading data from NVS!\n", esp_err_to_name(err));

    err = save_restart_counter();
    if (err != ESP_OK) printf("Error (%s) saving restart counter to NVS!\n", esp_err_to_name(err));

    gpio_pad_select_gpio(GPIO_NUM_0);
    gpio_set_direction(GPIO_NUM_0, GPIO_MODE_DEF_INPUT);

    /* Read the status of GPIO0. If GPIO0 is LOW for longer than 1000 ms,
       then save module's run time and restart it
     */
    while (1) {
        if (gpio_get_level(GPIO_NUM_0) == 0) {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            if(gpio_get_level(GPIO_NUM_0) == 0) {
                err = save_run_time();
                if (err != ESP_OK) printf("Error (%s) saving run time blob to NVS!\n", esp_err_to_name(err));
                printf("Restarting...\n");
                fflush(stdout);
                esp_restart();
            }
        }
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}