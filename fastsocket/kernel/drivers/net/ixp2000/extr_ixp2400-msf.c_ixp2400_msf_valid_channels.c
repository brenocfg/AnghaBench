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
typedef  int u32 ;

/* Variables and functions */
#define  IXP2400_RX_MODE_1x16_2x8 131 
#define  IXP2400_RX_MODE_1x32 130 
#define  IXP2400_RX_MODE_2x16 129 
#define  IXP2400_RX_MODE_4x8 128 
 int IXP2400_RX_MODE_MPHY ; 
 int IXP2400_RX_MODE_MPHY_32 ; 
 int IXP2400_RX_MODE_WIDTH_MASK ; 

__attribute__((used)) static u32 ixp2400_msf_valid_channels(u32 reg)
{
	u32 channels;

	channels = 0;
	switch (reg & IXP2400_RX_MODE_WIDTH_MASK) {
	case IXP2400_RX_MODE_1x32:
		channels = 0x1;
		if (reg & IXP2400_RX_MODE_MPHY &&
		    !(reg & IXP2400_RX_MODE_MPHY_32))
			channels = 0xf;
		break;

	case IXP2400_RX_MODE_2x16:
		channels = 0x5;
		break;

	case IXP2400_RX_MODE_4x8:
		channels = 0xf;
		break;

	case IXP2400_RX_MODE_1x16_2x8:
		channels = 0xd;
		break;
	}

	return channels;
}