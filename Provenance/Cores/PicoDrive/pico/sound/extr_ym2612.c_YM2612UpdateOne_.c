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
struct TYPE_4__ {int mode; } ;
struct TYPE_5__ {int pan; TYPE_1__ ST; } ;
struct TYPE_6__ {int slot_mask; int dacen; TYPE_2__ OPN; int /*<<< orphan*/ * CH; } ;

/* Variables and functions */
 int chan_render (int*,int,int,int) ; 
 int /*<<< orphan*/  chan_render_finish () ; 
 int /*<<< orphan*/  chan_render_prep () ; 
 int /*<<< orphan*/  memset32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refresh_fc_eg_chan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refresh_fc_eg_chan_sl3 () ; 
 TYPE_3__ ym2612 ; 

int YM2612UpdateOne_(int *buffer, int length, int stereo, int is_buf_empty)
{
	int pan;
	int active_chs = 0;

	// if !is_buf_empty, it means it has valid samples to mix with, else it may contain trash
	if (is_buf_empty) memset32(buffer, 0, length<<stereo);

/*
	{
		int c, s;
		ppp();
		for (c = 0; c < 6; c++) {
			int slr = 0, slm;
			printf("%i: ", c);
			for (s = 0; s < 4; s++) {
				if (ym2612.CH[c].SLOT[s].state != EG_OFF) slr = 1;
				printf(" %i", ym2612.CH[c].SLOT[s].state != EG_OFF);
			}
			slm = (ym2612.slot_mask&(0xf<<(c*4))) ? 1 : 0;
			printf(" | %i", slm);
			printf(" | %i\n", ym2612.CH[c].SLOT[SLOT1].Incr==-1);
			if (slr != slm) exit(1);
		}
	}
*/
	/* refresh PG and EG */
	refresh_fc_eg_chan( &ym2612.CH[0] );
	refresh_fc_eg_chan( &ym2612.CH[1] );
	if( (ym2612.OPN.ST.mode & 0xc0) )
		/* 3SLOT MODE */
		refresh_fc_eg_chan_sl3();
	else
		refresh_fc_eg_chan( &ym2612.CH[2] );
	refresh_fc_eg_chan( &ym2612.CH[3] );
	refresh_fc_eg_chan( &ym2612.CH[4] );
	refresh_fc_eg_chan( &ym2612.CH[5] );

	pan = ym2612.OPN.pan;
	if (stereo) stereo = 1;

	/* mix to 32bit dest */
	// flags: stereo, ?, disabled, ?, pan_r, pan_l
	chan_render_prep();
	if (ym2612.slot_mask & 0x00000f) active_chs |= chan_render(buffer, length, 0, stereo|((pan&0x003)<<4)) << 0;
	if (ym2612.slot_mask & 0x0000f0) active_chs |= chan_render(buffer, length, 1, stereo|((pan&0x00c)<<2)) << 1;
	if (ym2612.slot_mask & 0x000f00) active_chs |= chan_render(buffer, length, 2, stereo|((pan&0x030)   )) << 2;
	if (ym2612.slot_mask & 0x00f000) active_chs |= chan_render(buffer, length, 3, stereo|((pan&0x0c0)>>2)) << 3;
	if (ym2612.slot_mask & 0x0f0000) active_chs |= chan_render(buffer, length, 4, stereo|((pan&0x300)>>4)) << 4;
	if (ym2612.slot_mask & 0xf00000) active_chs |= chan_render(buffer, length, 5, stereo|((pan&0xc00)>>6)|(ym2612.dacen<<2)) << 5;
	chan_render_finish();

	return active_chs; // 1 if buffer updated
}