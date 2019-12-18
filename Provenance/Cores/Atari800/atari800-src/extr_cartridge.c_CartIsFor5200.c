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
#define  CARTRIDGE_5200_32 133 
#define  CARTRIDGE_5200_4 132 
#define  CARTRIDGE_5200_40 131 
#define  CARTRIDGE_5200_8 130 
#define  CARTRIDGE_5200_EE_16 129 
#define  CARTRIDGE_5200_NS_16 128 
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static int CartIsFor5200(int type)
{
	switch (type) {
	case CARTRIDGE_5200_32:
	case CARTRIDGE_5200_EE_16:
	case CARTRIDGE_5200_40:
	case CARTRIDGE_5200_NS_16:
	case CARTRIDGE_5200_8:
	case CARTRIDGE_5200_4:
		return TRUE;
	default:
		break;
	}
	return FALSE;
}