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
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {int tx_brk_done; } ;
struct TYPE_9__ {int tx_brk_done; } ;
struct TYPE_8__ {int txd_brk; } ;
struct TYPE_7__ {int tx_brk_num; } ;
struct TYPE_10__ {TYPE_1__ int_ena; TYPE_4__ int_clr; TYPE_3__ conf0; TYPE_2__ idle_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_5__** UART ; 
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uart_spinlock ; 

__attribute__((used)) static esp_err_t uart_set_break(uart_port_t uart_num, int break_num)
{
    UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
    UART[uart_num]->idle_conf.tx_brk_num = break_num;
    UART[uart_num]->conf0.txd_brk = 1;
    UART[uart_num]->int_clr.tx_brk_done = 1;
    UART[uart_num]->int_ena.tx_brk_done = 1;
    UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
    return ESP_OK;
}