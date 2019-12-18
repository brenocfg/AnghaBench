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
typedef  int mos65xx_address_mode ;

/* Variables and functions */
#define  MOS65XX_AM_ABS 141 
#define  MOS65XX_AM_ABSX 140 
#define  MOS65XX_AM_ABSY 139 
#define  MOS65XX_AM_ACC 138 
#define  MOS65XX_AM_IMM 137 
#define  MOS65XX_AM_IMP 136 
#define  MOS65XX_AM_IND 135 
#define  MOS65XX_AM_INDX 134 
#define  MOS65XX_AM_INDY 133 
#define  MOS65XX_AM_NONE 132 
#define  MOS65XX_AM_REL 131 
#define  MOS65XX_AM_ZP 130 
#define  MOS65XX_AM_ZPX 129 
#define  MOS65XX_AM_ZPY 128 

__attribute__((used)) static int getInstructionLength(mos65xx_address_mode am)
{
	switch(am) {
		case MOS65XX_AM_NONE:
		case MOS65XX_AM_ACC:
		case MOS65XX_AM_IMP:
			return 1;

		case MOS65XX_AM_IMM:
		case MOS65XX_AM_ZPX:
		case MOS65XX_AM_ZPY:
		case MOS65XX_AM_ZP:
		case MOS65XX_AM_REL:
		case MOS65XX_AM_INDX:
		case MOS65XX_AM_INDY:
			return 2;

		case MOS65XX_AM_ABS:
		case MOS65XX_AM_ABSX:
		case MOS65XX_AM_ABSY:
		case MOS65XX_AM_IND:
			return 3;
		default:
			return 1;
	}
}