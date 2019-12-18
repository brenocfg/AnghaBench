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
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ ANTIC_missile_dma_enabled ; 
 scalar_t__ ANTIC_missile_gra_enabled ; 
 scalar_t__ ANTIC_player_dma_enabled ; 
 scalar_t__ ANTIC_player_gra_enabled ; 
 int* ANTIC_xe_ptr ; 
 scalar_t__ ANTIC_xpos ; 
 int ANTIC_ypos ; 
 int GTIA_GRAFM ; 
 int GTIA_GRAFP0 ; 
 int GTIA_GRAFP1 ; 
 int GTIA_GRAFP2 ; 
 int GTIA_GRAFP3 ; 
 int GTIA_VDELAY ; 
 int MEMORY_dGetByte (int) ; 
 int* MEMORY_mem ; 
 int* hold_missiles_tab ; 
 int pmbase_d ; 
 int pmbase_s ; 
 scalar_t__ singleline ; 

__attribute__((used)) static void pmg_dma(void)
{
	/* VDELAY bit set == GTIA ignores PMG DMA in even lines */
	if (ANTIC_player_dma_enabled) {
		if (ANTIC_player_gra_enabled) {
			const UBYTE *base;
			if (singleline) {
				if (ANTIC_xe_ptr != NULL && pmbase_s < 0x8000 && pmbase_s >= 0x4000)
					base = ANTIC_xe_ptr + pmbase_s - 0x4000 + ANTIC_ypos;
				else
					base = MEMORY_mem + pmbase_s + ANTIC_ypos;
				if (ANTIC_ypos & 1) {
					GTIA_GRAFP0 = base[0x400];
					GTIA_GRAFP1 = base[0x500];
					GTIA_GRAFP2 = base[0x600];
					GTIA_GRAFP3 = base[0x700];
				}
				else {
					if ((GTIA_VDELAY & 0x10) == 0)
						GTIA_GRAFP0 = base[0x400];
					if ((GTIA_VDELAY & 0x20) == 0)
						GTIA_GRAFP1 = base[0x500];
					if ((GTIA_VDELAY & 0x40) == 0)
						GTIA_GRAFP2 = base[0x600];
					if ((GTIA_VDELAY & 0x80) == 0)
						GTIA_GRAFP3 = base[0x700];
				}
			}
			else {
				if (ANTIC_xe_ptr != NULL && pmbase_d < 0x8000 && pmbase_d >= 0x4000)
					base = ANTIC_xe_ptr + (pmbase_d - 0x4000) + (ANTIC_ypos >> 1);
				else
					base = MEMORY_mem + pmbase_d + (ANTIC_ypos >> 1);
				if (ANTIC_ypos & 1) {
					GTIA_GRAFP0 = base[0x200];
					GTIA_GRAFP1 = base[0x280];
					GTIA_GRAFP2 = base[0x300];
					GTIA_GRAFP3 = base[0x380];
				}
				else {
					if ((GTIA_VDELAY & 0x10) == 0)
						GTIA_GRAFP0 = base[0x200];
					if ((GTIA_VDELAY & 0x20) == 0)
						GTIA_GRAFP1 = base[0x280];
					if ((GTIA_VDELAY & 0x40) == 0)
						GTIA_GRAFP2 = base[0x300];
					if ((GTIA_VDELAY & 0x80) == 0)
						GTIA_GRAFP3 = base[0x380];
				}
			}
		}
		ANTIC_xpos += 4;
	}
	if (ANTIC_missile_dma_enabled) {
		if (ANTIC_missile_gra_enabled) {
			UBYTE data;
			if (ANTIC_xe_ptr != NULL && pmbase_s < 0x8000 && pmbase_s >= 0x4000)
				data = ANTIC_xe_ptr[singleline ? pmbase_s + ANTIC_ypos + 0x300 - 0x4000 : pmbase_d + (ANTIC_ypos >> 1) + 0x180 - 0x4000];
			else
				data = MEMORY_dGetByte(singleline ? pmbase_s + ANTIC_ypos + 0x300 : pmbase_d + (ANTIC_ypos >> 1) + 0x180);
			/* in odd lines load all missiles, in even only those, for which VDELAY bit is zero */
			GTIA_GRAFM = ANTIC_ypos & 1 ? data : ((GTIA_GRAFM ^ data) & hold_missiles_tab[GTIA_VDELAY & 0xf]) ^ data;
		}
		ANTIC_xpos++;
	}
}