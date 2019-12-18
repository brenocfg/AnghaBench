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
struct TYPE_2__ {int /*<<< orphan*/  read_lock; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  rx_func; int /*<<< orphan*/  tx_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  _lock_acquire_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release_recursive (int /*<<< orphan*/ *) ; 
 TYPE_1__** s_ctx ; 
 int /*<<< orphan*/  uart_rx_char_via_driver ; 
 int /*<<< orphan*/  uart_tx_char_via_driver ; 

void esp_vfs_dev_uart_use_driver(int uart_num)
{
    _lock_acquire_recursive(&s_ctx[uart_num]->read_lock);
    _lock_acquire_recursive(&s_ctx[uart_num]->write_lock);
    s_ctx[uart_num]->tx_func = uart_tx_char_via_driver;
    s_ctx[uart_num]->rx_func = uart_rx_char_via_driver;
    _lock_release_recursive(&s_ctx[uart_num]->write_lock);
    _lock_release_recursive(&s_ctx[uart_num]->read_lock);
}