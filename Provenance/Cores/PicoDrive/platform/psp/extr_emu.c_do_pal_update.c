#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* reg; } ;
struct TYPE_5__ {scalar_t__ dirtyPal; } ;
struct TYPE_8__ {TYPE_2__ video; TYPE_1__ m; int /*<<< orphan*/  cram; } ;
struct TYPE_7__ {int /*<<< orphan*/  gamma2; int /*<<< orphan*/  gamma; } ;

/* Variables and functions */
 int PDRAW_SPR_LO_ON_HI ; 
 TYPE_4__ Pico ; 
 TYPE_3__ currentConfig ; 
 int /*<<< orphan*/  do_pal_convert (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* localPal ; 
 int /*<<< orphan*/  memcpy32 (int*,void*,int) ; 
 int need_pal_upload ; 
 int rendstatus ; 

__attribute__((used)) static void do_pal_update(int allow_sh, int allow_as)
{
	unsigned int *dpal=(void *)localPal;
	int i;

	//for (i = 0x3f/2; i >= 0; i--)
	//	dpal[i] = ((spal[i]&0x000f000f)<< 1)|((spal[i]&0x00f000f0)<<3)|((spal[i]&0x0f000f00)<<4);
	do_pal_convert(localPal, Pico.cram, currentConfig.gamma, currentConfig.gamma2);

	Pico.m.dirtyPal = 0;
	need_pal_upload = 1;

	if (allow_sh && (Pico.video.reg[0xC]&8)) // shadow/hilight?
	{
		// shadowed pixels
		for (i = 0x3f/2; i >= 0; i--)
			dpal[0x20|i] = dpal[0x60|i] = (dpal[i]>>1)&0x7bcf7bcf;
		// hilighted pixels
		for (i = 0x3f; i >= 0; i--) {
			int t=localPal[i]&0xf79e;t+=0x4208;
			if (t&0x20) t|=0x1e;
			if (t&0x800) t|=0x780;
			if (t&0x10000) t|=0xf000;
			t&=0xf79e;
			localPal[0x80|i]=(unsigned short)t;
		}
		localPal[0xe0] = 0;
		localPal[0xf0] = 0x001f;
	}
	else if (allow_as && (rendstatus & PDRAW_SPR_LO_ON_HI))
	{
		memcpy32((int *)dpal+0x80/2, (void *)localPal, 0x40*2/4);
	}
}