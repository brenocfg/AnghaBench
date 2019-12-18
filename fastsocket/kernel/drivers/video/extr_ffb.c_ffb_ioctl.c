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
struct ffb_par {int /*<<< orphan*/  fbsize; } ;
struct fb_info {scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBTYPE_CREATOR ; 
 int sbusfb_ioctl_helper (unsigned int,unsigned long,struct fb_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ffb_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg)
{
	struct ffb_par *par = (struct ffb_par *)info->par;

	return sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_CREATOR, 24, par->fbsize);
}