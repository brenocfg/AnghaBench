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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_INT_CLR_REG (size_t) ; 
 int /*<<< orphan*/  UART_INT_ENA_REG (size_t) ; 
 size_t UART_NUM_MAX ; 
 int /*<<< orphan*/ * uart_spinlock ; 

esp_err_t uart_enable_intr_mask(uart_port_t uart_num, uint32_t enable_mask)
{
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
    SET_PERI_REG_MASK(UART_INT_CLR_REG(uart_num), enable_mask);
    SET_PERI_REG_MASK(UART_INT_ENA_REG(uart_num), enable_mask);
    UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
    return ESP_OK;
}