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
struct TYPE_3__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  ppp; int /*<<< orphan*/  uart_port; } ;
typedef  TYPE_1__ esp_modem_dte_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_MODEM_LINE_BUFFER_SIZE ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  pppos_input_tcpip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  uart_get_buffered_data_len (int /*<<< orphan*/ ,size_t*) ; 
 size_t uart_read_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_handle_uart_data(esp_modem_dte_t *esp_dte)
{
    size_t length = 0;
    uart_get_buffered_data_len(esp_dte->uart_port, &length);
    length = MIN(ESP_MODEM_LINE_BUFFER_SIZE, length);
    length = uart_read_bytes(esp_dte->uart_port, esp_dte->buffer, length, portMAX_DELAY);
    /* pass input data to the lwIP core thread */
    if (length) {
        pppos_input_tcpip(esp_dte->ppp, esp_dte->buffer, length);
    }
}