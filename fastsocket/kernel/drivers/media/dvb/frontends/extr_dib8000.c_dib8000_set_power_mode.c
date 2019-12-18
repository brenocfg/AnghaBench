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
typedef  int u16 ;
struct dib8000_state {int dummy; } ;
typedef  enum dib8000_power_mode { ____Placeholder_dib8000_power_mode } dib8000_power_mode ;

/* Variables and functions */
#define  DIB8000M_POWER_ALL 129 
#define  DIB8000M_POWER_INTERFACE_ONLY 128 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int,int,int) ; 

__attribute__((used)) static void dib8000_set_power_mode(struct dib8000_state *state, enum dib8000_power_mode mode)
{
	/* by default everything is going to be powered off */
	u16 reg_774 = 0x3fff, reg_775 = 0xffff, reg_776 = 0xffff,
	    reg_900 = (dib8000_read_word(state, 900) & 0xfffc) | 0x3, reg_1280 = (dib8000_read_word(state, 1280) & 0x00ff) | 0xff00;

	/* now, depending on the requested mode, we power on */
	switch (mode) {
		/* power up everything in the demod */
	case DIB8000M_POWER_ALL:
		reg_774 = 0x0000;
		reg_775 = 0x0000;
		reg_776 = 0x0000;
		reg_900 &= 0xfffc;
		reg_1280 &= 0x00ff;
		break;
	case DIB8000M_POWER_INTERFACE_ONLY:
		reg_1280 &= 0x00ff;
		break;
	}

	dprintk("powermode : 774 : %x ; 775 : %x; 776 : %x ; 900 : %x; 1280 : %x", reg_774, reg_775, reg_776, reg_900, reg_1280);
	dib8000_write_word(state, 774, reg_774);
	dib8000_write_word(state, 775, reg_775);
	dib8000_write_word(state, 776, reg_776);
	dib8000_write_word(state, 900, reg_900);
	dib8000_write_word(state, 1280, reg_1280);
}