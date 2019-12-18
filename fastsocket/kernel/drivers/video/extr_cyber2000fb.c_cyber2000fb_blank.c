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
struct fb_info {int dummy; } ;
struct cfb_info {int ramdac_powerdown; TYPE_1__* palette; } ;
struct TYPE_2__ {int red; int green; int blue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_SYNC_CTL ; 
 unsigned int EXT_SYNC_CTL_HS_0 ; 
 unsigned int EXT_SYNC_CTL_HS_NORMAL ; 
 unsigned int EXT_SYNC_CTL_VS_0 ; 
 unsigned int EXT_SYNC_CTL_VS_NORMAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 131 
#define  FB_BLANK_NORMAL 130 
#define  FB_BLANK_POWERDOWN 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int NR_PALETTE ; 
 int RAMDAC_BYPASS ; 
 int RAMDAC_DACPWRDN ; 
 int RAMDAC_RAMPWRDN ; 
 int /*<<< orphan*/  cyber2000_grphw (int /*<<< orphan*/ ,unsigned int,struct cfb_info*) ; 
 int /*<<< orphan*/  cyber2000fb_write_ramdac_ctrl (struct cfb_info*) ; 
 int /*<<< orphan*/  cyber2000fb_writeb (int,int,struct cfb_info*) ; 

__attribute__((used)) static int cyber2000fb_blank(int blank, struct fb_info *info)
{
	struct cfb_info *cfb = (struct cfb_info *)info;
	unsigned int sync = 0;
	int i;

	switch (blank) {
	case FB_BLANK_POWERDOWN:	/* powerdown - both sync lines down */
		sync = EXT_SYNC_CTL_VS_0 | EXT_SYNC_CTL_HS_0;
		break;
	case FB_BLANK_HSYNC_SUSPEND:	/* hsync off */
		sync = EXT_SYNC_CTL_VS_NORMAL | EXT_SYNC_CTL_HS_0;
		break;
	case FB_BLANK_VSYNC_SUSPEND:	/* vsync off */
		sync = EXT_SYNC_CTL_VS_0 | EXT_SYNC_CTL_HS_NORMAL;
		break;
	case FB_BLANK_NORMAL:		/* soft blank */
	default:			/* unblank */
		break;
	}

	cyber2000_grphw(EXT_SYNC_CTL, sync, cfb);

	if (blank <= 1) {
		/* turn on ramdacs */
		cfb->ramdac_powerdown &= ~(RAMDAC_DACPWRDN | RAMDAC_BYPASS |
					   RAMDAC_RAMPWRDN);
		cyber2000fb_write_ramdac_ctrl(cfb);
	}

	/*
	 * Soft blank/unblank the display.
	 */
	if (blank) {	/* soft blank */
		for (i = 0; i < NR_PALETTE; i++) {
			cyber2000fb_writeb(i, 0x3c8, cfb);
			cyber2000fb_writeb(0, 0x3c9, cfb);
			cyber2000fb_writeb(0, 0x3c9, cfb);
			cyber2000fb_writeb(0, 0x3c9, cfb);
		}
	} else {	/* unblank */
		for (i = 0; i < NR_PALETTE; i++) {
			cyber2000fb_writeb(i, 0x3c8, cfb);
			cyber2000fb_writeb(cfb->palette[i].red, 0x3c9, cfb);
			cyber2000fb_writeb(cfb->palette[i].green, 0x3c9, cfb);
			cyber2000fb_writeb(cfb->palette[i].blue, 0x3c9, cfb);
		}
	}

	if (blank >= 2) {
		/* turn off ramdacs */
		cfb->ramdac_powerdown |= RAMDAC_DACPWRDN | RAMDAC_BYPASS |
					 RAMDAC_RAMPWRDN;
		cyber2000fb_write_ramdac_ctrl(cfb);
	}

	return 0;
}