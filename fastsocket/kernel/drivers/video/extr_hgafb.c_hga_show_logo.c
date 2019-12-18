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
struct fb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void hga_show_logo(struct fb_info *info)
{
/*
	void __iomem *dest = hga_vram;
	char *logo = linux_logo_bw;
	int x, y;
	
	for (y = 134; y < 134 + 80 ; y++) * this needs some cleanup *
		for (x = 0; x < 10 ; x++)
			writeb(~*(logo++),(dest + HGA_ROWADDR(y) + x + 40));
*/
}