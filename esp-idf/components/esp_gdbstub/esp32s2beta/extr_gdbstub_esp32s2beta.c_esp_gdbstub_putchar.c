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
 int REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UART_FIFO_AHB_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_NUM ; 
 int /*<<< orphan*/  UART_STATUS_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_TXFIFO_CNT ; 

void esp_gdbstub_putchar(int c)
{
    while (REG_GET_FIELD(UART_STATUS_REG(UART_NUM), UART_TXFIFO_CNT) >= 126) {
        ;
    }
    REG_WRITE(UART_FIFO_AHB_REG(UART_NUM), c);
}