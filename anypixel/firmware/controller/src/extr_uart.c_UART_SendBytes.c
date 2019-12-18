#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int configured; int tx_buf_size; int TX_active; char* tx_buf; int /*<<< orphan*/  DMA_stream; int /*<<< orphan*/  USARTx; int /*<<< orphan*/  DR_ADDR; int /*<<< orphan*/  DMA_channel; int /*<<< orphan*/  DMA_IntFlags; } ;
struct TYPE_5__ {int DMA_BufferSize; int /*<<< orphan*/  DMA_PeripheralBurst; int /*<<< orphan*/  DMA_MemoryBurst; int /*<<< orphan*/  DMA_FIFOThreshold; int /*<<< orphan*/  DMA_FIFOMode; int /*<<< orphan*/  DMA_Priority; int /*<<< orphan*/  DMA_Mode; int /*<<< orphan*/  DMA_MemoryDataSize; int /*<<< orphan*/  DMA_PeripheralDataSize; int /*<<< orphan*/  DMA_MemoryInc; int /*<<< orphan*/  DMA_PeripheralInc; int /*<<< orphan*/  DMA_DIR; scalar_t__ DMA_Memory0BaseAddr; int /*<<< orphan*/  DMA_PeripheralBaseAddr; int /*<<< orphan*/  DMA_Channel; } ;
typedef  TYPE_1__ DMA_InitTypeDef ;
typedef  TYPE_2__ CONFIG_USART_ConfigState ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGPIN_CLR (int) ; 
 int /*<<< orphan*/  DEBUGPIN_SET (int) ; 
 int /*<<< orphan*/  DEBUGPIN_TGL (int) ; 
 int /*<<< orphan*/  DMA_ClearITPendingBit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_Cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_DIR_MemoryToPeripheral ; 
 int /*<<< orphan*/  DMA_DeInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FIFOMode_Disable ; 
 int /*<<< orphan*/  DMA_FIFOThreshold_3QuartersFull ; 
 int /*<<< orphan*/  DMA_Init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  DMA_MemoryBurst_Single ; 
 int /*<<< orphan*/  DMA_MemoryDataSize_Byte ; 
 int /*<<< orphan*/  DMA_MemoryInc_Enable ; 
 int /*<<< orphan*/  DMA_Mode_Normal ; 
 int /*<<< orphan*/  DMA_PeripheralBurst_Single ; 
 int /*<<< orphan*/  DMA_PeripheralDataSize_Byte ; 
 int /*<<< orphan*/  DMA_PeripheralInc_Disable ; 
 int /*<<< orphan*/  DMA_Priority_VeryHigh ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  USART_ClearFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_DMACmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_DMAReq_Tx ; 
 int /*<<< orphan*/  USART_FLAG_TC ; 
 int /*<<< orphan*/  USART_ITConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USART_IT_TC ; 
 int /*<<< orphan*/  assert (int) ; 

bool UART_SendBytes(CONFIG_USART_ConfigState *cfg, const char *buf, uint16_t length) {
	DMA_InitTypeDef DMA_InitStructure;
	int i;

	assert(cfg->configured == true);
	assert(buf != NULL);
	assert(length <= cfg->tx_buf_size);

    DEBUGPIN_SET(2);

	if(cfg->TX_active) {
        DEBUGPIN_CLR(2);
        DEBUGPIN_TGL(9);
		return false;
	}

	for(i = 0; i < length; i++)
		cfg->tx_buf[i] = buf[i];

	// clear transmission complete flag and enable TC interrupt to
	// allow fast response to switch back to RX mode
	USART_ClearFlag(cfg->USARTx, USART_FLAG_TC);
	USART_ITConfig(cfg->USARTx, USART_IT_TC, ENABLE);
	DMA_ClearITPendingBit(cfg->DMA_stream, cfg->DMA_IntFlags);

	// configure DMA
    DMA_DeInit(cfg->DMA_stream);
	DMA_InitStructure.DMA_Channel = cfg->DMA_channel;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cfg->DR_ADDR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)cfg->tx_buf;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = length;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_3QuartersFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(cfg->DMA_stream, &DMA_InitStructure);

	// start the transfer
	USART_DMACmd(cfg->USARTx, USART_DMAReq_Tx, ENABLE);
	DMA_Cmd(cfg->DMA_stream, ENABLE);

    cfg->TX_active = true;

    DEBUGPIN_CLR(2);
	return true;
}