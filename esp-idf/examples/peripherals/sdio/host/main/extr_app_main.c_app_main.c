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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_slave_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int CONFIG_FREERTOS_HZ ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  job_fifo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  job_getint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  job_write_reg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  process_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slave_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slave_power_on () ; 
 int /*<<< orphan*/  slave_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int xTaskGetTickCount () ; 

void app_main(void)
{
    esp_slave_context_t context;
    esp_err_t err;

    //enable the power if on espressif SDIO master-slave board
    slave_power_on();

    ESP_LOGI(TAG, "host ready, start initializing slave...");

    err = slave_init(&context);
    ESP_ERROR_CHECK(err);

    err = slave_reset(&context);
    ESP_ERROR_CHECK(err);

    uint32_t start, end;

    job_write_reg(&context, 10);

    int times = 2;

    while (1) {
        job_getint(&context);
        start = xTaskGetTickCount();
        while (1) {
            process_event(&context);
            vTaskDelay(1);
            end = xTaskGetTickCount();
            if ((end - start) * 1000 / CONFIG_FREERTOS_HZ > 5000) {
                break;
            }
        }
        if (--times == 0) {
            break;
        }
    };

    while (1) {
        job_fifo(&context);

        start = xTaskGetTickCount();
        while (1) {
            process_event(&context);
            vTaskDelay(1);
            end = xTaskGetTickCount();
            if ((end - start) * 1000 / CONFIG_FREERTOS_HZ > 2000) {
                break;
            }
        }
    }
}