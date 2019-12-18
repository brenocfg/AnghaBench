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
 int /*<<< orphan*/  CONFIG_ESP_CONSOLE_UART_NUM ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_FIFO_AHB_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_STATUS_REG (int /*<<< orphan*/ ) ; 
 int UART_TXFIFO_CNT ; 
 int UART_TXFIFO_CNT_S ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void panicPutChar(char c)
{
    while (((READ_PERI_REG(UART_STATUS_REG(CONFIG_ESP_CONSOLE_UART_NUM)) >> UART_TXFIFO_CNT_S)&UART_TXFIFO_CNT) >= 126) ;
    WRITE_PERI_REG(UART_FIFO_AHB_REG(CONFIG_ESP_CONSOLE_UART_NUM), c);
}