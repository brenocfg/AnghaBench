#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct my_timming {int VDisplay; int VSyncStart; int VSyncEnd; int VTotal; int HTotal; int HDisplay; int HSyncEnd; int HSyncStart; int sync; scalar_t__ interlaced; } ;
struct TYPE_9__ {int xres_virtual; int bits_per_pixel; } ;
struct TYPE_10__ {TYPE_3__ var; } ;
struct matroxfb_dh_fb_info {int interlaced; TYPE_4__ fbcon; struct matrox_fb_info* primary_dev; } ;
struct TYPE_11__ {int ctl; } ;
struct TYPE_12__ {TYPE_5__ crtc2; } ;
struct TYPE_7__ {scalar_t__ g450dac; } ;
struct matrox_fb_info {TYPE_6__ hw; TYPE_2__* outputs; TYPE_1__ devflags; } ;
struct TYPE_8__ {scalar_t__ src; scalar_t__ mode; } ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 scalar_t__ MATROXFB_OUTPUT_MODE_MONITOR ; 
 scalar_t__ MATROXFB_SRC_CRTC2 ; 
 int mga_inl (int) ; 
 int /*<<< orphan*/  mga_outl (int,int) ; 

__attribute__((used)) static void matroxfb_dh_restore(struct matroxfb_dh_fb_info* m2info,
		struct my_timming* mt,
		int mode,
		unsigned int pos) {
	u_int32_t tmp;
	u_int32_t datactl;
	struct matrox_fb_info *minfo = m2info->primary_dev;

	switch (mode) {
		case 15:
			tmp = 0x00200000;
			break;
		case 16:
			tmp = 0x00400000;
			break;
/*		case 32: */
		default:
			tmp = 0x00800000;
			break;
	}
	tmp |= 0x00000001;	/* enable CRTC2 */
	datactl = 0;
	if (minfo->outputs[1].src == MATROXFB_SRC_CRTC2) {
		if (minfo->devflags.g450dac) {
			tmp |= 0x00000006; /* source from secondary pixel PLL */
			/* no vidrst when in monitor mode */
			if (minfo->outputs[1].mode != MATROXFB_OUTPUT_MODE_MONITOR) {
				tmp |=  0xC0001000; /* Enable H/V vidrst */
			}
		} else {
			tmp |= 0x00000002; /* source from VDOCLK */
			tmp |= 0xC0000000; /* enable vvidrst & hvidrst */
			/* MGA TVO is our clock source */
		}
	} else if (minfo->outputs[0].src == MATROXFB_SRC_CRTC2) {
		tmp |= 0x00000004; /* source from pixclock */
		/* PIXPLL is our clock source */
	}
	if (minfo->outputs[0].src == MATROXFB_SRC_CRTC2) {
		tmp |= 0x00100000;	/* connect CRTC2 to DAC */
	}
	if (mt->interlaced) {
		tmp |= 0x02000000;	/* interlaced, second field is bigger, as G450 apparently ignores it */
		mt->VDisplay >>= 1;
		mt->VSyncStart >>= 1;
		mt->VSyncEnd >>= 1;
		mt->VTotal >>= 1;
	}
	if ((mt->HTotal & 7) == 2) {
		datactl |= 0x00000010;
		mt->HTotal &= ~7;
	}
	tmp |= 0x10000000;	/* 0x10000000 is VIDRST polarity */
	mga_outl(0x3C14, ((mt->HDisplay - 8) << 16) | (mt->HTotal - 8));
	mga_outl(0x3C18, ((mt->HSyncEnd - 8) << 16) | (mt->HSyncStart - 8));
	mga_outl(0x3C1C, ((mt->VDisplay - 1) << 16) | (mt->VTotal - 1));
	mga_outl(0x3C20, ((mt->VSyncEnd - 1) << 16) | (mt->VSyncStart - 1));
	mga_outl(0x3C24, ((mt->VSyncStart) << 16) | (mt->HSyncStart));	/* preload */
	{
		u_int32_t linelen = m2info->fbcon.var.xres_virtual * (m2info->fbcon.var.bits_per_pixel >> 3);
		if (tmp & 0x02000000) {
			/* field #0 is smaller, so... */
			mga_outl(0x3C2C, pos);			/* field #1 vmemory start */
			mga_outl(0x3C28, pos + linelen);	/* field #0 vmemory start */
			linelen <<= 1;
			m2info->interlaced = 1;
		} else {
			mga_outl(0x3C28, pos);		/* vmemory start */
			m2info->interlaced = 0;
		}
		mga_outl(0x3C40, linelen);
	}
	mga_outl(0x3C4C, datactl);	/* data control */
	if (tmp & 0x02000000) {
		int i;

		mga_outl(0x3C10, tmp & ~0x02000000);
		for (i = 0; i < 2; i++) {
			unsigned int nl;
			unsigned int lastl = 0;

			while ((nl = mga_inl(0x3C48) & 0xFFF) >= lastl) {
				lastl = nl;
			}
		}
	}
	mga_outl(0x3C10, tmp);
	minfo->hw.crtc2.ctl = tmp;

	tmp = mt->VDisplay << 16;	/* line compare */
	if (mt->sync & FB_SYNC_HOR_HIGH_ACT)
		tmp |= 0x00000100;
	if (mt->sync & FB_SYNC_VERT_HIGH_ACT)
		tmp |= 0x00000200;
	mga_outl(0x3C44, tmp);
}