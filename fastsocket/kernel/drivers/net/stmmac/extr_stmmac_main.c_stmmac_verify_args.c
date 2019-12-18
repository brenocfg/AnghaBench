#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ BUF_SIZE_16KiB ; 
 scalar_t__ DMA_BUFFER_SIZE ; 
 scalar_t__ DMA_RX_SIZE ; 
 scalar_t__ DMA_TX_SIZE ; 
 int FLOW_AUTO ; 
 int FLOW_OFF ; 
 int PAUSE_TIME ; 
 scalar_t__ TX_TIMEO ; 
 scalar_t__ buf_sz ; 
 scalar_t__ dma_rxsize ; 
 scalar_t__ dma_txsize ; 
 int flow_ctrl ; 
 scalar_t__ likely (int) ; 
 int pause ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ watchdog ; 

__attribute__((used)) static void stmmac_verify_args(void)
{
	if (unlikely(watchdog < 0))
		watchdog = TX_TIMEO;
	if (unlikely(dma_rxsize < 0))
		dma_rxsize = DMA_RX_SIZE;
	if (unlikely(dma_txsize < 0))
		dma_txsize = DMA_TX_SIZE;
	if (unlikely((buf_sz < DMA_BUFFER_SIZE) || (buf_sz > BUF_SIZE_16KiB)))
		buf_sz = DMA_BUFFER_SIZE;
	if (unlikely(flow_ctrl > 1))
		flow_ctrl = FLOW_AUTO;
	else if (likely(flow_ctrl < 0))
		flow_ctrl = FLOW_OFF;
	if (unlikely((pause < 0) || (pause > 0xffff)))
		pause = PAUSE_TIME;

	return;
}