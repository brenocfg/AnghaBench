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
#define  CH_IMEM_STREAM0_DEST 148 
#define  CH_IMEM_STREAM0_SRC 147 
#define  CH_IMEM_STREAM1_DEST 146 
#define  CH_IMEM_STREAM1_SRC 145 
#define  CH_MEM_STREAM0_DEST 144 
#define  CH_MEM_STREAM0_SRC 143 
#define  CH_MEM_STREAM1_DEST 142 
#define  CH_MEM_STREAM1_SRC 141 
#define  CH_MEM_STREAM2_DEST 140 
#define  CH_MEM_STREAM2_SRC 139 
#define  CH_MEM_STREAM3_DEST 138 
#define  CH_MEM_STREAM3_SRC 137 
#define  CH_PPI0 136 
#define  CH_PPI1 135 
#define  CH_SPI 134 
#define  CH_SPORT0_RX 133 
#define  CH_SPORT0_TX 132 
#define  CH_SPORT1_RX 131 
#define  CH_SPORT1_TX 130 
#define  CH_UART_RX 129 
#define  CH_UART_TX 128 
 int IRQ_IMEM_DMA0 ; 
 int IRQ_IMEM_DMA1 ; 
 int IRQ_MEM_DMA0 ; 
 int IRQ_MEM_DMA1 ; 
 int IRQ_MEM_DMA2 ; 
 int IRQ_MEM_DMA3 ; 
 int IRQ_PPI0 ; 
 int IRQ_PPI1 ; 
 int IRQ_SPI ; 
 int IRQ_SPORT0_RX ; 
 int IRQ_SPORT0_TX ; 
 int IRQ_SPORT1_RX ; 
 int IRQ_SPORT1_TX ; 
 int IRQ_UART_RX ; 
 int IRQ_UART_TX ; 

int channel2irq(unsigned int channel)
{
	int ret_irq = -1;

	switch (channel) {
	case CH_PPI0:
		ret_irq = IRQ_PPI0;
		break;
	case CH_PPI1:
		ret_irq = IRQ_PPI1;
		break;
	case CH_SPORT0_RX:
		ret_irq = IRQ_SPORT0_RX;
		break;
	case CH_SPORT0_TX:
		ret_irq = IRQ_SPORT0_TX;
		break;
	case CH_SPORT1_RX:
		ret_irq = IRQ_SPORT1_RX;
		break;
	case CH_SPORT1_TX:
		ret_irq = IRQ_SPORT1_TX;
		break;
	case CH_SPI:
		ret_irq = IRQ_SPI;
		break;
	case CH_UART_RX:
		ret_irq = IRQ_UART_RX;
		break;
	case CH_UART_TX:
		ret_irq = IRQ_UART_TX;
		break;

	case CH_MEM_STREAM0_SRC:
	case CH_MEM_STREAM0_DEST:
		ret_irq = IRQ_MEM_DMA0;
		break;
	case CH_MEM_STREAM1_SRC:
	case CH_MEM_STREAM1_DEST:
		ret_irq = IRQ_MEM_DMA1;
		break;
	case CH_MEM_STREAM2_SRC:
	case CH_MEM_STREAM2_DEST:
		ret_irq = IRQ_MEM_DMA2;
		break;
	case CH_MEM_STREAM3_SRC:
	case CH_MEM_STREAM3_DEST:
		ret_irq = IRQ_MEM_DMA3;
		break;

	case CH_IMEM_STREAM0_SRC:
	case CH_IMEM_STREAM0_DEST:
		ret_irq = IRQ_IMEM_DMA0;
		break;
	case CH_IMEM_STREAM1_SRC:
	case CH_IMEM_STREAM1_DEST:
		ret_irq = IRQ_IMEM_DMA1;
		break;
	}
	return ret_irq;
}