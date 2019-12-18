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

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  SPP_DATA_LEN ; 
 int /*<<< orphan*/  SPP_TAG ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int portTICK_PERIOD_MS ; 
 int read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spp_data ; 
 int /*<<< orphan*/  spp_wr_task_shut_down () ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void spp_read_handle(void * param)
{
    int size = 0;
    int fd = (int)param;
    do {
        size = read (fd, spp_data, SPP_DATA_LEN);
        ESP_LOGI(SPP_TAG, "fd = %d data_len = %d", fd, size);
        if (size == -1) {
            break;
        }
        esp_log_buffer_hex(SPP_TAG, spp_data, size);
        if (size == 0) {
            /*read fail due to there is no data, retry after 1s*/
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    } while (1);
    spp_wr_task_shut_down();
}