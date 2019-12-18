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
#define  CH_MEM_STREAM0_DEST 153 
#define  CH_MEM_STREAM0_SRC 152 
#define  CH_MEM_STREAM1_DEST 151 
#define  CH_MEM_STREAM1_SRC 150 
#define  CH_MEM_STREAM2_DEST 149 
#define  CH_MEM_STREAM2_SRC 148 
#define  CH_MEM_STREAM3_DEST 147 
#define  CH_MEM_STREAM3_SRC 146 
#define  CH_PPI 145 
#define  CH_SPI0 144 
#define  CH_SPI1 143 
#define  CH_SPI2 142 
#define  CH_SPORT0_RX 141 
#define  CH_SPORT0_TX 140 
#define  CH_SPORT1_RX 139 
#define  CH_SPORT1_TX 138 
#define  CH_SPORT2_RX 137 
#define  CH_SPORT2_TX 136 
#define  CH_SPORT3_RX 135 
#define  CH_SPORT3_TX 134 
#define  CH_UART0_RX 133 
#define  CH_UART0_TX 132 
#define  CH_UART1_RX 131 
#define  CH_UART1_TX 130 
#define  CH_UART2_RX 129 
#define  CH_UART2_TX 128 
 int IRQ_MEM0_DMA0 ; 
 int IRQ_MEM0_DMA1 ; 
 int IRQ_MEM1_DMA0 ; 
 int IRQ_MEM1_DMA1 ; 
 int IRQ_PPI ; 
 int IRQ_SPI0 ; 
 int IRQ_SPI1 ; 
 int IRQ_SPI2 ; 
 int IRQ_SPORT0_RX ; 
 int IRQ_SPORT0_TX ; 
 int IRQ_SPORT1_RX ; 
 int IRQ_SPORT1_TX ; 
 int IRQ_SPORT2_RX ; 
 int IRQ_SPORT2_TX ; 
 int IRQ_SPORT3_RX ; 
 int IRQ_SPORT3_TX ; 
 int IRQ_UART0_RX ; 
 int IRQ_UART0_TX ; 
 int IRQ_UART1_RX ; 
 int IRQ_UART1_TX ; 
 int IRQ_UART2_RX ; 
 int IRQ_UART2_TX ; 

int channel2irq(unsigned int channel)
{
	int ret_irq = -1;

	switch (channel) {
	case CH_PPI:
		ret_irq = IRQ_PPI;
		break;

	case CH_UART0_RX:
		ret_irq = IRQ_UART0_RX;
		break;

	case CH_UART0_TX:
		ret_irq = IRQ_UART0_TX;
		break;

	case CH_UART1_RX:
		ret_irq = IRQ_UART1_RX;
		break;

	case CH_UART1_TX:
		ret_irq = IRQ_UART1_TX;
		break;

	case CH_UART2_RX:
		ret_irq = IRQ_UART2_RX;
		break;

	case CH_UART2_TX:
		ret_irq = IRQ_UART2_TX;
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

	case CH_SPORT2_RX:
		ret_irq = IRQ_SPORT2_RX;
		break;

	case CH_SPORT2_TX:
		ret_irq = IRQ_SPORT2_TX;
		break;

	case CH_SPORT3_RX:
		ret_irq = IRQ_SPORT3_RX;
		break;

	case CH_SPORT3_TX:
		ret_irq = IRQ_SPORT3_TX;
		break;

	case CH_SPI0:
		ret_irq = IRQ_SPI0;
		break;

	case CH_SPI1:
		ret_irq = IRQ_SPI1;
		break;

	case CH_SPI2:
		ret_irq = IRQ_SPI2;
		break;

	case CH_MEM_STREAM0_SRC:
	case CH_MEM_STREAM0_DEST:
		ret_irq = IRQ_MEM0_DMA0;
		break;
	case CH_MEM_STREAM1_SRC:
	case CH_MEM_STREAM1_DEST:
		ret_irq = IRQ_MEM0_DMA1;
		break;
	case CH_MEM_STREAM2_SRC:
	case CH_MEM_STREAM2_DEST:
		ret_irq = IRQ_MEM1_DMA0;
		break;
	case CH_MEM_STREAM3_SRC:
	case CH_MEM_STREAM3_DEST:
		ret_irq = IRQ_MEM1_DMA1;
		break;
	}
	return ret_irq;
}