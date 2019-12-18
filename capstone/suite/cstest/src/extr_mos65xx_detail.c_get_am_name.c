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

__attribute__((used)) static const char *get_am_name(mos65xx_address_mode mode)
{
	switch(mode) {
		default:
		case MOS65XX_AM_NONE:
			return "No address mode";
		case MOS65XX_AM_IMP:
			return "implied addressing (no addressing mode)";
		case MOS65XX_AM_ACC:
			return "accumulator addressing";
		case MOS65XX_AM_ABS:
			return "absolute addressing";
		case MOS65XX_AM_ZP:
			return "zeropage addressing";
		case MOS65XX_AM_IMM:
			return "8 Bit immediate value";
		case MOS65XX_AM_ABSX:
			return "indexed absolute addressing by the X index register";
		case MOS65XX_AM_ABSY:
			return "indexed absolute addressing by the Y index register";
		case MOS65XX_AM_INDX:
			return "indexed indirect addressing by the X index register";
		case MOS65XX_AM_INDY:
			return "indirect indexed addressing by the Y index register";
		case MOS65XX_AM_ZPX:
			return "indexed zeropage addressing by the X index register";
		case MOS65XX_AM_ZPY:
			return "indexed zeropage addressing by the Y index register";
		case MOS65XX_AM_REL:
			return "relative addressing used by branches";
		case MOS65XX_AM_IND:
			return "absolute indirect addressing";
	}
}