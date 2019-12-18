#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct imstt_par {int /*<<< orphan*/  dc_regs; } ;
struct fb_var_screeninfo {int yoffset; int xoffset; int bits_per_pixel; } ;
struct TYPE_2__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; struct imstt_par* par; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SSR ; 
 int /*<<< orphan*/  write_reg_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
set_offset (struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct imstt_par *par = info->par;
	__u32 off = var->yoffset * (info->fix.line_length >> 3)
		    + ((var->xoffset * (var->bits_per_pixel >> 3)) >> 3);
	write_reg_le32(par->dc_regs, SSR, off);
}