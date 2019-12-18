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
typedef  int u32 ;
struct pm2fb_par {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int) ; 
 int PM2F_HSYNC_ACT_HIGH ; 
 int PM2F_HSYNC_ACT_LOW ; 
 int PM2F_HSYNC_MASK ; 
 int PM2F_RD_PALETTE_WIDTH_8 ; 
 int PM2F_VSYNC_ACT_HIGH ; 
 int PM2F_VSYNC_ACT_LOW ; 
 int PM2F_VSYNC_MASK ; 
 int /*<<< orphan*/  PM2I_RD_MISC_CONTROL ; 
 int /*<<< orphan*/  PM2R_VIDEO_CONTROL ; 
 int /*<<< orphan*/  PM2VI_RD_SYNC_CONTROL ; 
#define  PM2_TYPE_PERMEDIA2 129 
#define  PM2_TYPE_PERMEDIA2V 128 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  pm2_RDAC_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm2v_RDAC_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_video(struct pm2fb_par *p, u32 video)
{
	u32 tmp;
	u32 vsync = video;

	DPRINTK("video = 0x%x\n", video);

	/*
	 * The hardware cursor needs +vsync to recognise vert retrace.
	 * We may not be using the hardware cursor, but the X Glint
	 * driver may well. So always set +hsync/+vsync and then set
	 * the RAMDAC to invert the sync if necessary.
	 */
	vsync &= ~(PM2F_HSYNC_MASK | PM2F_VSYNC_MASK);
	vsync |= PM2F_HSYNC_ACT_HIGH | PM2F_VSYNC_ACT_HIGH;

	WAIT_FIFO(p, 3);
	pm2_WR(p, PM2R_VIDEO_CONTROL, vsync);

	switch (p->type) {
	case PM2_TYPE_PERMEDIA2:
		tmp = PM2F_RD_PALETTE_WIDTH_8;
		if ((video & PM2F_HSYNC_MASK) == PM2F_HSYNC_ACT_LOW)
			tmp |= 4; /* invert hsync */
		if ((video & PM2F_VSYNC_MASK) == PM2F_VSYNC_ACT_LOW)
			tmp |= 8; /* invert vsync */
		pm2_RDAC_WR(p, PM2I_RD_MISC_CONTROL, tmp);
		break;
	case PM2_TYPE_PERMEDIA2V:
		tmp = 0;
		if ((video & PM2F_HSYNC_MASK) == PM2F_HSYNC_ACT_LOW)
			tmp |= 1; /* invert hsync */
		if ((video & PM2F_VSYNC_MASK) == PM2F_VSYNC_ACT_LOW)
			tmp |= 4; /* invert vsync */
		pm2v_RDAC_WR(p, PM2VI_RD_SYNC_CONTROL, tmp);
		break;
	}
}