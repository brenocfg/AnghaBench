#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  size_t uart_port_t ;
struct TYPE_6__ {int tx_done; } ;
struct TYPE_5__ {scalar_t__ sw_rts; } ;
struct TYPE_7__ {scalar_t__ txfifo_cnt; } ;
struct TYPE_8__ {TYPE_2__ int_ena; TYPE_1__ conf0; TYPE_3__ status; } ;

/* Variables and functions */
 TYPE_4__** UART ; 
 int /*<<< orphan*/  UART_FIFO_AHB_REG (size_t) ; 
 scalar_t__ UART_FIFO_LEN ; 
 scalar_t__ UART_IS_MODE_SET (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_MODE_RS485_HALF_DUPLEX ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,char const) ; 

__attribute__((used)) static int uart_fill_fifo(uart_port_t uart_num, const char *buffer, uint32_t len)
{
    uint8_t i = 0;
    uint8_t tx_fifo_cnt = UART[uart_num]->status.txfifo_cnt;
    uint8_t tx_remain_fifo_cnt = (UART_FIFO_LEN - tx_fifo_cnt);
    uint8_t copy_cnt = (len >= tx_remain_fifo_cnt ? tx_remain_fifo_cnt : len);
    // Set the RTS pin if RS485 mode is enabled
    if (UART_IS_MODE_SET(uart_num, UART_MODE_RS485_HALF_DUPLEX)) {
        UART[uart_num]->conf0.sw_rts = 0;
        UART[uart_num]->int_ena.tx_done = 1;
    }
    for (i = 0; i < copy_cnt; i++) {
        WRITE_PERI_REG(UART_FIFO_AHB_REG(uart_num), buffer[i]);
    }
    return copy_cnt;
}