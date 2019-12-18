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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (char const*,char*,int const,scalar_t__*) ; 
 int /*<<< orphan*/  ESP_LOG_BUFFER_HEXDUMP (char const*,scalar_t__*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOG_INFO ; 
 scalar_t__ RX_BUF_SIZE ; 
 int /*<<< orphan*/  UART_NUM_1 ; 
 int /*<<< orphan*/  esp_log_level_set (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int portTICK_RATE_MS ; 
 int uart_read_bytes (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int) ; 

__attribute__((used)) static void rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "RX_TASK";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE+1);
    while (1) {
        const int rxBytes = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE, 1000 / portTICK_RATE_MS);
        if (rxBytes > 0) {
            data[rxBytes] = 0;
            ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
            ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);
        }
    }
    free(data);
}