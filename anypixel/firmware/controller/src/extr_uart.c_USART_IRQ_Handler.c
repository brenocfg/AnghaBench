#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int SR; int /*<<< orphan*/  DR; } ;
struct TYPE_6__ {int configured; int TX_active; TYPE_2__* USARTx; int /*<<< orphan*/  rx_fifo; int /*<<< orphan*/  frame_available; int /*<<< orphan*/  DMA_stream; } ;
typedef  TYPE_1__ CONFIG_USART_ConfigState ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGPIN_CLR (int) ; 
 int /*<<< orphan*/  DEBUGPIN_SET (int) ; 
 int /*<<< orphan*/  DEBUGPIN_TGL (int) ; 
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  DMA_Cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_DeInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIFO_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIFO_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_DMACmd (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_DMAReq_Tx ; 
 int USART_FLAG_IDLE ; 
 int USART_FLAG_RXNE ; 
 int USART_FLAG_TC ; 
 int /*<<< orphan*/  USART_ITConfig (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_IT_TC ; 
 int /*<<< orphan*/  USART_ReceiveData (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 

void USART_IRQ_Handler(CONFIG_USART_ConfigState *cfg) {
	uint8_t workByte;
	uint16_t status = cfg->USARTx->SR;

	assert(cfg->configured == true);
    DEBUGPIN_SET(3);
	if(status & USART_FLAG_RXNE) {
        DEBUGPIN_TGL(4);
		// we have a new byte to receive
		//workByte = USART_ReceiveData(cfg->USARTx); // bypass wrapper function to speed up ISR
		workByte = cfg->USARTx->DR;

		FIFO_write(cfg->rx_fifo, workByte);
	}
	if( (cfg->TX_active) && (status & USART_FLAG_TC) ) {
        DEBUGPIN_TGL(5);
		// disable the interrupt since transmission will remain complete until we start a new one
		USART_ITConfig(cfg->USARTx, USART_IT_TC, DISABLE);

		// transmission has completed so disable DMA and update TX_active flag
		DMA_Cmd(cfg->DMA_stream, DISABLE);
		DMA_DeInit(cfg->DMA_stream);
		USART_DMACmd(cfg->USARTx, USART_DMAReq_Tx, DISABLE);
		cfg->TX_active = false;
	}
    if(status & USART_FLAG_IDLE) {
        DEBUGPIN_TGL(6);
        // got idle state so next byte will be start of packet
        cfg->frame_available = FIFO_available(cfg->rx_fifo);
        // need to read from the data register to clear this interrupt flag
        workByte = USART_ReceiveData(cfg->USARTx);
	}
	DEBUGPIN_CLR(3);
}