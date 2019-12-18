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
typedef  int u32 ;
struct tdfx_par {int dummy; } ;
struct fb_var_screeninfo {int yoffset; scalar_t__ xoffset; } ;
struct TYPE_2__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; struct tdfx_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VIDDESKSTART ; 
 int /*<<< orphan*/  banshee_make_room (struct tdfx_par*,int) ; 
 scalar_t__ nopan ; 
 int /*<<< orphan*/  tdfx_outl (struct tdfx_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tdfxfb_pan_display(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	struct tdfx_par *par = info->par;
	u32 addr = var->yoffset * info->fix.line_length;

	if (nopan || var->xoffset)
		return -EINVAL;

	banshee_make_room(par, 1);
	tdfx_outl(par, VIDDESKSTART, addr);

	return 0;
}