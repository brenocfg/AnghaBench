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
typedef  int /*<<< orphan*/  esp_line_endings_t ;
struct TYPE_2__ {int /*<<< orphan*/  rx_mode; } ;

/* Variables and functions */
 int UART_NUM ; 
 TYPE_1__** s_ctx ; 

void esp_vfs_dev_uart_set_rx_line_endings(esp_line_endings_t mode)
{
    for (int i = 0; i < UART_NUM; ++i) {
        s_ctx[i]->rx_mode = mode;
    }
}