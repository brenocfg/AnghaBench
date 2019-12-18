#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int rw_byte; } ;
struct TYPE_7__ {int rw_byte; } ;
struct TYPE_6__ {int txfifo_cnt; } ;
struct TYPE_9__ {TYPE_3__ ahb_fifo; TYPE_2__ fifo; TYPE_1__ status; } ;
typedef  TYPE_4__ uart_dev_t ;
struct TYPE_10__ {TYPE_4__* uart; } ;

/* Variables and functions */
 TYPE_5__** s_ctx ; 

__attribute__((used)) static void uart_tx_char(int fd, int c)
{
    uart_dev_t* uart = s_ctx[fd]->uart;
    while (uart->status.txfifo_cnt >= 127) {
        ;
    }
#if CONFIG_IDF_TARGET_ESP32
    uart->fifo.rw_byte = c;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    uart->ahb_fifo.rw_byte = c;
#endif
}