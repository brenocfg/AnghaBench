#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ cr01; scalar_t__ pixclock; } ;
struct i810fb_par {int ovract; TYPE_1__ regs; } ;
struct fb_var_screeninfo {int right_margin; int hsync_len; int left_margin; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* std_modes ; 

void i810fb_encode_registers(const struct fb_var_screeninfo *var,
			     struct i810fb_par *par, u32 xres, u32 yres)
{ 
	u32 diff = 0, diff_best = 0xFFFFFFFF, i = 0, i_best = 0; 
	u8 hfl;

	hfl = (u8) ((xres >> 3) - 1);
	for (i = 0; i < ARRAY_SIZE(std_modes); i++) { 
		if (std_modes[i].cr01 == hfl) { 
			if (std_modes[i].pixclock <= par->regs.pixclock)
				diff = par->regs.pixclock - 
					std_modes[i].pixclock;
			if (diff < diff_best) {	 
		    		i_best = i;
		    		diff_best = diff;
			}
		}
	}
	par->regs = std_modes[i_best];

	/* overlay */
	par->ovract = ((xres + var->right_margin + var->hsync_len + 
			var->left_margin - 32) | ((xres - 32) << 16));
}