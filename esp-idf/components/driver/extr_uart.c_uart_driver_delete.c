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
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  periph_module_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/ * tx_ring_buf; int /*<<< orphan*/ * rx_ring_buf; int /*<<< orphan*/ * xQueueUart; int /*<<< orphan*/ * rx_mux; int /*<<< orphan*/ * tx_mux; int /*<<< orphan*/ * tx_brk_sem; int /*<<< orphan*/ * tx_done_sem; int /*<<< orphan*/ * tx_fifo_sem; int /*<<< orphan*/  intr_handle; } ;

/* Variables and functions */
 size_t CONFIG_ESP_CONSOLE_UART_NUM ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 size_t UART_NUM_MAX ; 
 int /*<<< orphan*/  UART_TAG ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  get_periph_module (size_t) ; 
 TYPE_1__** p_uart_obj ; 
 int /*<<< orphan*/  periph_module_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_disable_rx_intr (size_t) ; 
 int /*<<< orphan*/  uart_disable_tx_intr (size_t) ; 
 int /*<<< orphan*/  uart_pattern_link_free (size_t) ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vRingbufferDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 

esp_err_t uart_driver_delete(uart_port_t uart_num)
{
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    if (p_uart_obj[uart_num] == NULL) {
        ESP_LOGI(UART_TAG, "ALREADY NULL");
        return ESP_OK;
    }
    esp_intr_free(p_uart_obj[uart_num]->intr_handle);
    uart_disable_rx_intr(uart_num);
    uart_disable_tx_intr(uart_num);
    uart_pattern_link_free(uart_num);

    if (p_uart_obj[uart_num]->tx_fifo_sem) {
        vSemaphoreDelete(p_uart_obj[uart_num]->tx_fifo_sem);
        p_uart_obj[uart_num]->tx_fifo_sem = NULL;
    }
    if (p_uart_obj[uart_num]->tx_done_sem) {
        vSemaphoreDelete(p_uart_obj[uart_num]->tx_done_sem);
        p_uart_obj[uart_num]->tx_done_sem = NULL;
    }
    if (p_uart_obj[uart_num]->tx_brk_sem) {
        vSemaphoreDelete(p_uart_obj[uart_num]->tx_brk_sem);
        p_uart_obj[uart_num]->tx_brk_sem = NULL;
    }
    if (p_uart_obj[uart_num]->tx_mux) {
        vSemaphoreDelete(p_uart_obj[uart_num]->tx_mux);
        p_uart_obj[uart_num]->tx_mux = NULL;
    }
    if (p_uart_obj[uart_num]->rx_mux) {
        vSemaphoreDelete(p_uart_obj[uart_num]->rx_mux);
        p_uart_obj[uart_num]->rx_mux = NULL;
    }
    if (p_uart_obj[uart_num]->xQueueUart) {
        vQueueDelete(p_uart_obj[uart_num]->xQueueUart);
        p_uart_obj[uart_num]->xQueueUart = NULL;
    }
    if (p_uart_obj[uart_num]->rx_ring_buf) {
        vRingbufferDelete(p_uart_obj[uart_num]->rx_ring_buf);
        p_uart_obj[uart_num]->rx_ring_buf = NULL;
    }
    if (p_uart_obj[uart_num]->tx_ring_buf) {
        vRingbufferDelete(p_uart_obj[uart_num]->tx_ring_buf);
        p_uart_obj[uart_num]->tx_ring_buf = NULL;
    }

    free(p_uart_obj[uart_num]);
    p_uart_obj[uart_num] = NULL;

    if (uart_num != CONFIG_ESP_CONSOLE_UART_NUM) {
       periph_module_t periph_module = get_periph_module(uart_num);
       periph_module_disable(periph_module);
    }
    return ESP_OK;
}