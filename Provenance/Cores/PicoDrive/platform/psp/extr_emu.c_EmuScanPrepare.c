#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* reg; } ;
struct TYPE_5__ {scalar_t__ dirtyPal; } ;
struct TYPE_6__ {TYPE_1__ video; TYPE_2__ m; } ;

/* Variables and functions */
 unsigned char* HighCol ; 
 int PDRAW_SPR_LO_ON_HI ; 
 TYPE_3__ Pico ; 
 scalar_t__ VRAM_CACHED_STUFF ; 
 int /*<<< orphan*/  amips_clut ; 
 int /*<<< orphan*/  amips_clut_6bit ; 
 int /*<<< orphan*/  amips_clut_f ; 
 int /*<<< orphan*/  do_pal_update (int,int) ; 
 scalar_t__ dynamic_palette ; 
 int rendstatus ; 

__attribute__((used)) static void EmuScanPrepare(void)
{
	HighCol = (unsigned char *)VRAM_CACHED_STUFF + 8;
	if (!(Pico.video.reg[1]&8)) HighCol += 8*512;

	if (dynamic_palette > 0)
		dynamic_palette--;

	if (Pico.m.dirtyPal)
		do_pal_update(1, 1);
	if ((rendstatus & PDRAW_SPR_LO_ON_HI) && !(Pico.video.reg[0xC]&8))
	     amips_clut_f = amips_clut_6bit;
	else amips_clut_f = amips_clut;
}