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
struct fb_info {int /*<<< orphan*/  node; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svga_wcrt_mask (int,int,int) ; 
 int /*<<< orphan*/  svga_wseq_mask (int,int,int) ; 

__attribute__((used)) static int s3fb_blank(int blank_mode, struct fb_info *info)
{
	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		pr_debug("fb%d: unblank\n", info->node);
		svga_wcrt_mask(0x56, 0x00, 0x06);
		svga_wseq_mask(0x01, 0x00, 0x20);
		break;
	case FB_BLANK_NORMAL:
		pr_debug("fb%d: blank\n", info->node);
		svga_wcrt_mask(0x56, 0x00, 0x06);
		svga_wseq_mask(0x01, 0x20, 0x20);
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		pr_debug("fb%d: hsync\n", info->node);
		svga_wcrt_mask(0x56, 0x02, 0x06);
		svga_wseq_mask(0x01, 0x20, 0x20);
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		pr_debug("fb%d: vsync\n", info->node);
		svga_wcrt_mask(0x56, 0x04, 0x06);
		svga_wseq_mask(0x01, 0x20, 0x20);
		break;
	case FB_BLANK_POWERDOWN:
		pr_debug("fb%d: sync down\n", info->node);
		svga_wcrt_mask(0x56, 0x06, 0x06);
		svga_wseq_mask(0x01, 0x20, 0x20);
		break;
	}

	return 0;
}