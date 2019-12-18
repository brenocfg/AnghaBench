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
 int /*<<< orphan*/  MASK1 ; 
 int /*<<< orphan*/  MASK2 ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DisableDmaChannel(unsigned int channel)
{
	switch (channel) {	// 8 Bit DMA channels DMAC1
	case 0:
		outb(4, MASK1);	//mask channel 0
		break;
	case 1:
		outb(5, MASK1);	//Mask channel 1
		break;
	case 2:
		outb(6, MASK1);	//Mask channel 2
		break;
	case 3:
		outb(7, MASK1);	//Mask channel 3
		break;
	case 5:
		outb(5, MASK2);	//Mask channel 5
		break;
	case 6:
		outb(6, MASK2);	//Mask channel 6
		break;
	case 7:
		outb(7, MASK2);	//Mask channel 7
		break;
	default:
		break;
	};			//Switch
}