#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; } ;
typedef  TYPE_1__ uart_event_t ;
struct TYPE_7__ {int /*<<< orphan*/  event_loop_hdl; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  uart_port; } ;
typedef  TYPE_2__ esp_modem_dte_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  MODEM_TAG ; 
#define  UART_BREAK 134 
#define  UART_BUFFER_FULL 133 
#define  UART_DATA 132 
#define  UART_FIFO_OVF 131 
#define  UART_FRAME_ERR 130 
#define  UART_PARITY_ERR 129 
#define  UART_PATTERN_DET 128 
 int /*<<< orphan*/  esp_event_loop_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_handle_uart_data (TYPE_2__*) ; 
 int /*<<< orphan*/  esp_handle_uart_pattern (TYPE_2__*) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int /*<<< orphan*/  uart_flush_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ xQueueReceive (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xQueueReset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uart_event_task_entry(void *param)
{
    esp_modem_dte_t *esp_dte = (esp_modem_dte_t *)param;
    uart_event_t event;
    while (1) {
        if (xQueueReceive(esp_dte->event_queue, &event, pdMS_TO_TICKS(100))) {
            switch (event.type) {
            case UART_DATA:
                esp_handle_uart_data(esp_dte);
                break;
            case UART_FIFO_OVF:
                ESP_LOGW(MODEM_TAG, "HW FIFO Overflow");
                uart_flush_input(esp_dte->uart_port);
                xQueueReset(esp_dte->event_queue);
                break;
            case UART_BUFFER_FULL:
                ESP_LOGW(MODEM_TAG, "Ring Buffer Full");
                uart_flush_input(esp_dte->uart_port);
                xQueueReset(esp_dte->event_queue);
                break;
            case UART_BREAK:
                ESP_LOGW(MODEM_TAG, "Rx Break");
                break;
            case UART_PARITY_ERR:
                ESP_LOGE(MODEM_TAG, "Parity Error");
                break;
            case UART_FRAME_ERR:
                ESP_LOGE(MODEM_TAG, "Frame Error");
                break;
            case UART_PATTERN_DET:
                esp_handle_uart_pattern(esp_dte);
                break;
            default:
                ESP_LOGW(MODEM_TAG, "unknown uart event type: %d", event.type);
                break;
            }
        }
        /* Drive the event loop */
        esp_event_loop_run(esp_dte->event_loop_hdl, pdMS_TO_TICKS(50));
    }
    vTaskDelete(NULL);
}