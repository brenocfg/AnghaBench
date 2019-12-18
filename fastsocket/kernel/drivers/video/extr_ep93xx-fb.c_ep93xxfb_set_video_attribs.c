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
struct fb_info {struct ep93xx_fbi* par; } ;
struct ep93xx_fbi {TYPE_1__* mach_info; } ;
struct TYPE_2__ {unsigned int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XXFB_ATTRIBS ; 
 unsigned int EP93XXFB_ENABLE ; 
 int /*<<< orphan*/  ep93xxfb_out_locked (struct ep93xx_fbi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xxfb_set_video_attribs(struct fb_info *info)
{
	struct ep93xx_fbi *fbi = info->par;
	unsigned int attribs;

	attribs = EP93XXFB_ENABLE;
	attribs |= fbi->mach_info->flags;
	ep93xxfb_out_locked(fbi, attribs, EP93XXFB_ATTRIBS);
}