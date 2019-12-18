#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int configured; int /*<<< orphan*/  rx_fifo; } ;
typedef  TYPE_1__ CONFIG_USART_ConfigState ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

uint16_t UART_RX_available(CONFIG_USART_ConfigState *cfg) {
	assert(cfg->configured == true);

	return FIFO_available(cfg->rx_fifo);
}