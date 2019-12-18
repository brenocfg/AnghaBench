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
typedef  int /*<<< orphan*/  uart_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  UART_AT_CMD_CHAR_DET_INT_ENA_M ; 
 int /*<<< orphan*/  uart_disable_intr_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t uart_disable_pattern_det_intr(uart_port_t uart_num)
{
    return uart_disable_intr_mask(uart_num, UART_AT_CMD_CHAR_DET_INT_ENA_M);
}