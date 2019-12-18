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
struct TYPE_6__ {int rw_byte; } ;
struct TYPE_5__ {scalar_t__ rxfifo_cnt; } ;
struct TYPE_7__ {TYPE_2__ fifo; TYPE_1__ status; } ;
typedef  TYPE_3__ uart_dev_t ;
struct TYPE_8__ {TYPE_3__* uart; } ;

/* Variables and functions */
 int NONE ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_FIFO_AHB_REG (int) ; 
 TYPE_4__** s_ctx ; 

__attribute__((used)) static int uart_rx_char(int fd)
{
    uart_dev_t* uart = s_ctx[fd]->uart;
    if (uart->status.rxfifo_cnt == 0) {
        return NONE;
    }
#if CONFIG_IDF_TARGET_ESP32
    return uart->fifo.rw_byte;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    return READ_PERI_REG(UART_FIFO_AHB_REG(fd));
#endif
}