#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uart_port_t ;
struct TYPE_2__ {int rx_buffer_full_flg; int /*<<< orphan*/  uart_num; scalar_t__ rx_stash_len; int /*<<< orphan*/  rx_buffered_len; int /*<<< orphan*/  rx_data_buf; int /*<<< orphan*/  rx_ring_buf; } ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 TYPE_1__** p_uart_obj ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  uart_enable_rx_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uart_spinlock ; 
 scalar_t__ xRingbufferSend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static bool uart_check_buf_full(uart_port_t uart_num)
{
    if (p_uart_obj[uart_num]->rx_buffer_full_flg) {
        BaseType_t res = xRingbufferSend(p_uart_obj[uart_num]->rx_ring_buf, p_uart_obj[uart_num]->rx_data_buf, p_uart_obj[uart_num]->rx_stash_len, 1);
        if (res == pdTRUE) {
            UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
            p_uart_obj[uart_num]->rx_buffered_len += p_uart_obj[uart_num]->rx_stash_len;
            p_uart_obj[uart_num]->rx_buffer_full_flg = false;
            UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
            uart_enable_rx_intr(p_uart_obj[uart_num]->uart_num);
            return true;
        }
    }
    return false;
}