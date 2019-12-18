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
struct fb_cmap {scalar_t__ start; int len; int /*<<< orphan*/ * transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  int /*<<< orphan*/  color ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int aafb_set_cmap(struct fb_cmap *cmap, int kspc, int con,
			 struct fb_info *info)
{
	u16 color[2] = {0x0000, 0x000f};

	if (cmap->start == 0
	    && cmap->len == 2
	    && memcmp(cmap->red, color, sizeof(color)) == 0
	    && memcmp(cmap->green, color, sizeof(color)) == 0
	    && memcmp(cmap->blue, color, sizeof(color)) == 0
	    && cmap->transp == NULL)
		return 0;
	else
		return -EINVAL;
}