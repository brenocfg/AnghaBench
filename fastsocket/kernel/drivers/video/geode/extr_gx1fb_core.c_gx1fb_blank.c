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
struct geodefb_par {TYPE_1__* vid_ops; } ;
struct fb_info {struct geodefb_par* par; } ;
struct TYPE_2__ {int (* blank_display ) (struct fb_info*,int) ;} ;

/* Variables and functions */
 int stub1 (struct fb_info*,int) ; 

__attribute__((used)) static int gx1fb_blank(int blank_mode, struct fb_info *info)
{
	struct geodefb_par *par = info->par;

	return par->vid_ops->blank_display(info, blank_mode);
}