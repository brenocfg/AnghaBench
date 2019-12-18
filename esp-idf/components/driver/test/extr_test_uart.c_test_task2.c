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
 int /*<<< orphan*/  UART_NUM1 ; 
 int /*<<< orphan*/  UART_TX_DONE_INT_ENA_M ; 
 int exit_flag ; 
 int /*<<< orphan*/  uart_disable_intr_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_task2(void *pvParameters)
{
    while (exit_flag == false) {
        // This task obstruct a setting tx_done_sem semaphore in the UART interrupt.
        // It leads to waiting the ticks_to_wait time in uart_wait_tx_done() function.
        uart_disable_intr_mask(UART_NUM1, UART_TX_DONE_INT_ENA_M);
    }
    vTaskDelete(NULL);
}