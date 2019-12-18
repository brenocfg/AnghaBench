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
typedef  int /*<<< orphan*/  dma_t ;

/* Variables and functions */
#define  DMA_0 131 
#define  DMA_1 130 
#define  DMA_2 129 
#define  DMA_3 128 
 int /*<<< orphan*/  IOMD_DMATCR ; 
 int iomd_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomd_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iomd_set_dma_speed(unsigned int chan, dma_t *dma, int cycle)
{
	int tcr, speed;

	if (cycle < 188)
		speed = 3;
	else if (cycle <= 250)
		speed = 2;
	else if (cycle < 438)
		speed = 1;
	else
		speed = 0;

	tcr = iomd_readb(IOMD_DMATCR);
	speed &= 3;

	switch (chan) {
	case DMA_0:
		tcr = (tcr & ~0x03) | speed;
		break;

	case DMA_1:
		tcr = (tcr & ~0x0c) | (speed << 2);
		break;

	case DMA_2:
		tcr = (tcr & ~0x30) | (speed << 4);
		break;

	case DMA_3:
		tcr = (tcr & ~0xc0) | (speed << 6);
		break;

	default:
		break;
	}

	iomd_writeb(tcr, IOMD_DMATCR);

	return speed;
}