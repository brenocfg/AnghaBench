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
struct bttv_tvnorm {int swidth; int totalwidth; int scaledtwidth; int vdelay; int hdelayx1; int sheight; int /*<<< orphan*/  vtotal; } ;
struct bttv_geometry {int hscale; int hdelay; int vscale; int crop; int vdelay; int width; int sheight; int vtc; int comb; int /*<<< orphan*/  vtotal; } ;
struct bttv {scalar_t__ input; scalar_t__ dig; scalar_t__ opt_combfilter; } ;

/* Variables and functions */
 int BT848_VSCALE_INT ; 

__attribute__((used)) static void
bttv_calc_geo_old(struct bttv *btv, struct bttv_geometry *geo,
		  int width, int height, int interleaved,
		  const struct bttv_tvnorm *tvnorm)
{
	u32 xsf, sr;
	int vdelay;

	int swidth       = tvnorm->swidth;
	int totalwidth   = tvnorm->totalwidth;
	int scaledtwidth = tvnorm->scaledtwidth;

	if (btv->input == btv->dig) {
		swidth       = 720;
		totalwidth   = 858;
		scaledtwidth = 858;
	}

	vdelay = tvnorm->vdelay;

	xsf = (width*scaledtwidth)/swidth;
	geo->hscale =  ((totalwidth*4096UL)/xsf-4096);
	geo->hdelay =  tvnorm->hdelayx1;
	geo->hdelay =  (geo->hdelay*width)/swidth;
	geo->hdelay &= 0x3fe;
	sr = ((tvnorm->sheight >> (interleaved?0:1))*512)/height - 512;
	geo->vscale =  (0x10000UL-sr) & 0x1fff;
	geo->crop   =  ((width>>8)&0x03) | ((geo->hdelay>>6)&0x0c) |
		((tvnorm->sheight>>4)&0x30) | ((vdelay>>2)&0xc0);
	geo->vscale |= interleaved ? (BT848_VSCALE_INT<<8) : 0;
	geo->vdelay  =  vdelay;
	geo->width   =  width;
	geo->sheight =  tvnorm->sheight;
	geo->vtotal  =  tvnorm->vtotal;

	if (btv->opt_combfilter) {
		geo->vtc  = (width < 193) ? 2 : ((width < 385) ? 1 : 0);
		geo->comb = (width < 769) ? 1 : 0;
	} else {
		geo->vtc  = 0;
		geo->comb = 0;
	}
}