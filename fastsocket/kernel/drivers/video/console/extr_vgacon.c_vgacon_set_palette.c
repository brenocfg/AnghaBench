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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_IS_VISIBLE (struct vc_data*) ; 
 int EINVAL ; 
 scalar_t__ VIDEO_TYPE_VGAC ; 
 scalar_t__ vga_palette_blanked ; 
 int /*<<< orphan*/  vga_set_palette (struct vc_data*,unsigned char*) ; 
 scalar_t__ vga_video_type ; 

__attribute__((used)) static int vgacon_set_palette(struct vc_data *vc, unsigned char *table)
{
#ifdef CAN_LOAD_PALETTE
	if (vga_video_type != VIDEO_TYPE_VGAC || vga_palette_blanked
	    || !CON_IS_VISIBLE(vc))
		return -EINVAL;
	vga_set_palette(vc, table);
	return 0;
#else
	return -EINVAL;
#endif
}