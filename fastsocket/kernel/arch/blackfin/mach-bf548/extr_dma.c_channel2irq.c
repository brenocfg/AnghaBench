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
#define  CH_EPPI0 157 
#define  CH_EPPI1 156 
#define  CH_EPPI2 155 
#define  CH_MEM_STREAM0_DEST 154 
#define  CH_MEM_STREAM0_SRC 153 
#define  CH_MEM_STREAM1_DEST 152 
#define  CH_MEM_STREAM1_SRC 151 
#define  CH_MEM_STREAM2_DEST 150 
#define  CH_MEM_STREAM2_SRC 149 
#define  CH_MEM_STREAM3_DEST 148 
#define  CH_MEM_STREAM3_SRC 147 
#define  CH_PIXC_IMAGE 146 
#define  CH_PIXC_OUTPUT 145 
#define  CH_PIXC_OVERLAY 144 
#define  CH_SDH 143 
#define  CH_SPI0 142 
#define  CH_SPI1 141 
#define  CH_SPI2 140 
#define  CH_SPORT0_RX 139 
#define  CH_SPORT0_TX 138 
#define  CH_SPORT1_RX 137 
#define  CH_SPORT1_TX 136 
#define  CH_SPORT2_RX 135 
#define  CH_SPORT2_TX 134 
#define  CH_SPORT3_RX 133 
#define  CH_SPORT3_TX 132 
#define  CH_UART0_RX 131 
#define  CH_UART0_TX 130 
#define  CH_UART1_RX 129 
#define  CH_UART1_TX 128 
 int IRQ_EPPI0 ; 
 int IRQ_EPPI1 ; 
 int IRQ_EPPI2 ; 
 int IRQ_MDMAS0 ; 
 int IRQ_MDMAS1 ; 
 int IRQ_MDMAS2 ; 
 int IRQ_MDMAS3 ; 
 int IRQ_PIXC_IN0 ; 
 int IRQ_PIXC_IN1 ; 
 int IRQ_PIXC_OUT ; 
 int IRQ_SDH ; 
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

int channel2irq(unsigned int channel)
{
	int ret_irq = -1;

	switch (channel) {
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
	case CH_SPI0:
		ret_irq = IRQ_SPI0;
		break;
	case CH_SPI1:
		ret_irq = IRQ_SPI1;
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
	case CH_EPPI0:
		ret_irq = IRQ_EPPI0;
		break;
	case CH_EPPI1:
		ret_irq = IRQ_EPPI1;
		break;
	case CH_EPPI2:
		ret_irq = IRQ_EPPI2;
		break;
	case CH_PIXC_IMAGE:
		ret_irq = IRQ_PIXC_IN0;
		break;
	case CH_PIXC_OVERLAY:
		ret_irq = IRQ_PIXC_IN1;
		break;
	case CH_PIXC_OUTPUT:
		ret_irq = IRQ_PIXC_OUT;
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
	case CH_SDH:
		ret_irq = IRQ_SDH;
		break;
	case CH_SPI2:
		ret_irq = IRQ_SPI2;
		break;
	case CH_MEM_STREAM0_SRC:
	case CH_MEM_STREAM0_DEST:
		ret_irq = IRQ_MDMAS0;
		break;
	case CH_MEM_STREAM1_SRC:
	case CH_MEM_STREAM1_DEST:
		ret_irq = IRQ_MDMAS1;
		break;
	case CH_MEM_STREAM2_SRC:
	case CH_MEM_STREAM2_DEST:
		ret_irq = IRQ_MDMAS2;
		break;
	case CH_MEM_STREAM3_SRC:
	case CH_MEM_STREAM3_DEST:
		ret_irq = IRQ_MDMAS3;
		break;
	}
	return ret_irq;
}