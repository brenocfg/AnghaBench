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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uart_port_t ;

/* Variables and functions */
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_STATUS_REG (int /*<<< orphan*/ ) ; 
 int UART_ST_UTX_OUT_M ; 
 int UART_TXFIFO_CNT_M ; 

void uart_wait_tx_idle_polling(uart_port_t uart_num)
{
    uint32_t status;
    do {
        status = READ_PERI_REG(UART_STATUS_REG(uart_num));
        /* either tx count or state is non-zero */
    } while ((status & (UART_ST_UTX_OUT_M | UART_TXFIFO_CNT_M)) != 0);
}