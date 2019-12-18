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
struct TYPE_2__ {int xres_virtual; int bits_per_pixel; int yres; } ;
struct vout_fbdev {int top_border; int buffer_count; int fb_size; scalar_t__ mem; TYPE_1__ fbvar_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void vout_fbdev_clear_lines(struct vout_fbdev *fbdev, int y, int count)
{
	int stride = fbdev->fbvar_new.xres_virtual * fbdev->fbvar_new.bits_per_pixel / 8;
	int i;

	if (y + count > fbdev->top_border + fbdev->fbvar_new.yres)
		count = fbdev->top_border + fbdev->fbvar_new.yres - y;

	if (y >= 0 && count > 0)
		for (i = 0; i < fbdev->buffer_count; i++)
			memset((char *)fbdev->mem + fbdev->fb_size * i + y * stride, 0, stride * count);
}