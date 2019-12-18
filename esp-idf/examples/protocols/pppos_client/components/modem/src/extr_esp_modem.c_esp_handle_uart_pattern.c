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
struct TYPE_4__ {char* buffer; int /*<<< orphan*/  uart_port; } ;
typedef  TYPE_1__ esp_modem_dte_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 int ESP_MODEM_LINE_BUFFER_SIZE ; 
 int /*<<< orphan*/  MODEM_TAG ; 
 int /*<<< orphan*/  esp_dte_handle_line (TYPE_1__*) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int /*<<< orphan*/  uart_flush (int /*<<< orphan*/ ) ; 
 int uart_pattern_pop_pos (int /*<<< orphan*/ ) ; 
 int uart_read_bytes (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_handle_uart_pattern(esp_modem_dte_t *esp_dte)
{
    int pos = uart_pattern_pop_pos(esp_dte->uart_port);
    int read_len = 0;
    if (pos != -1) {
        if (pos < ESP_MODEM_LINE_BUFFER_SIZE - 1) {
            /* read one line(include '\n') */
            read_len = pos + 1;
        } else {
            ESP_LOGW(MODEM_TAG, "ESP Modem Line buffer too small");
            read_len = ESP_MODEM_LINE_BUFFER_SIZE - 1;
        }
        read_len = uart_read_bytes(esp_dte->uart_port, esp_dte->buffer, read_len, pdMS_TO_TICKS(100));
        if (read_len) {
            /* make sure the line is a standard string */
            esp_dte->buffer[read_len] = '\0';
            /* Send new line to handle */
            esp_dte_handle_line(esp_dte);
        } else {
            ESP_LOGE(MODEM_TAG, "uart read bytes failed");
        }
    } else {
        ESP_LOGW(MODEM_TAG, "Pattern Queue Size too small");
        uart_flush(esp_dte->uart_port);
    }
}