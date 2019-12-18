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
 scalar_t__ REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_FIFO_AHB_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_NUM ; 
 int /*<<< orphan*/  UART_RXFIFO_CNT ; 
 int /*<<< orphan*/  UART_STATUS_REG (int /*<<< orphan*/ ) ; 

int esp_gdbstub_getchar()
{
    while (REG_GET_FIELD(UART_STATUS_REG(UART_NUM), UART_RXFIFO_CNT) == 0) {
        ;
    }
    return REG_READ(UART_FIFO_AHB_REG(UART_NUM));
}