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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int configured; int TX_active; int /*<<< orphan*/  USARTx; int /*<<< orphan*/  rx_fifo; } ;
typedef  TYPE_1__ CONFIG_USART_ConfigState ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  FIFO_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RESET ; 
 scalar_t__ USART_GetITStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_ITConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_IT_RXNE ; 
 int /*<<< orphan*/  USART_IT_TC ; 
 int /*<<< orphan*/  USART_ReceiveData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

void USART_IRQ_Handler(CONFIG_USART_ConfigState *cfg) {
	uint8_t workByte;

	assert(cfg->configured == true);

	if(USART_GetITStatus(cfg->USARTx, USART_IT_RXNE) != RESET) {
		// we have a new byte to receive
		workByte = USART_ReceiveData(cfg->USARTx);
		FIFO_write(cfg->rx_fifo, workByte);
	}
	if(USART_GetITStatus(cfg->USARTx, USART_IT_TC) != RESET) {
		// disable the interrupt since transmission will remain complete until we start a new one
		USART_ITConfig(cfg->USARTx, USART_IT_TC, DISABLE);

		cfg->TX_active = false;
	}
}