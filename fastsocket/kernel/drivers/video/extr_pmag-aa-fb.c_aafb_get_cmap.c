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
struct fb_info {int dummy; } ;
struct fb_cmap {int member_1; int* member_2; int* member_3; int* member_4; int /*<<< orphan*/ * member_5; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_copy_cmap (struct fb_cmap*,struct fb_cmap*,int) ; 

__attribute__((used)) static int aafb_get_cmap(struct fb_cmap *cmap, int kspc, int con,
			 struct fb_info *info)
{
	static u16 color[2] = {0x0000, 0x000f};
	static struct fb_cmap aafb_cmap = {0, 2, color, color, color, NULL};

	fb_copy_cmap(&aafb_cmap, cmap, kspc ? 0 : 2);
	return 0;
}