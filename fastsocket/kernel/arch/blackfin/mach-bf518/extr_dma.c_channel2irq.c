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
#define  CH_EMAC_RX 143 
#define  CH_EMAC_TX 142 
#define  CH_MEM_STREAM0_DEST 141 
#define  CH_MEM_STREAM0_SRC 140 
#define  CH_MEM_STREAM1_DEST 139 
#define  CH_MEM_STREAM1_SRC 138 
#define  CH_PPI 137 
#define  CH_SPI0 136 
#define  CH_SPORT0_RX 135 
#define  CH_SPORT0_TX 134 
#define  CH_SPORT1_RX 133 
#define  CH_SPORT1_TX 132 
#define  CH_UART0_RX 131 
#define  CH_UART0_TX 130 
#define  CH_UART1_RX 129 
#define  CH_UART1_TX 128 
 int IRQ_MAC_RX ; 
 int IRQ_MAC_TX ; 
 int IRQ_MEM_DMA0 ; 
 int IRQ_MEM_DMA1 ; 
 int IRQ_PPI ; 
 int IRQ_SPI0 ; 
 int IRQ_SPORT0_RX ; 
 int IRQ_SPORT0_TX ; 
 int IRQ_SPORT1_RX ; 
 int IRQ_SPORT1_TX ; 
 int IRQ_UART0_RX ; 
 int IRQ_UART0_TX ; 
 int IRQ_UART1_RX ; 
 int IRQ_UART1_TX ; 

int channel2irq(unsigned int channel)
{
	int ret_irq = -1;

	switch (channel) {
	case CH_PPI:
		ret_irq = IRQ_PPI;
		break;

	case CH_EMAC_RX:
		ret_irq = IRQ_MAC_RX;
		break;

	case CH_EMAC_TX:
		ret_irq = IRQ_MAC_TX;
		break;

	case CH_UART1_RX:
		ret_irq = IRQ_UART1_RX;
		break;

	case CH_UART1_TX:
		ret_irq = IRQ_UART1_TX;
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

	case CH_SPI0:
		ret_irq = IRQ_SPI0;
		break;

	case CH_UART0_RX:
		ret_irq = IRQ_UART0_RX;
		break;

	case CH_UART0_TX:
		ret_irq = IRQ_UART0_TX;
		break;

	case CH_MEM_STREAM0_SRC:
	case CH_MEM_STREAM0_DEST:
		ret_irq = IRQ_MEM_DMA0;
		break;

	case CH_MEM_STREAM1_SRC:
	case CH_MEM_STREAM1_DEST:
		ret_irq = IRQ_MEM_DMA1;
		break;
	}
	return ret_irq;
}