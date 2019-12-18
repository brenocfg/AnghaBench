#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/ * intr_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 size_t UART_NUM_MAX ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ *) ; 
 TYPE_1__** p_uart_obj ; 
 int /*<<< orphan*/ * uart_spinlock ; 

esp_err_t uart_isr_free(uart_port_t uart_num)
{
    esp_err_t ret;
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    if (p_uart_obj[uart_num]->intr_handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
    ret = esp_intr_free(p_uart_obj[uart_num]->intr_handle);
    p_uart_obj[uart_num]->intr_handle = NULL;
    UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
    return ret;
}