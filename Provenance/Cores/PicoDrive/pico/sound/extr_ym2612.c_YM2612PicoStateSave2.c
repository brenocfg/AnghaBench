#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int state_phase; int keyon_field; int magic; int TAT; int TBT; int /*<<< orphan*/  lfo_ampm; int /*<<< orphan*/  lfo_cnt; int /*<<< orphan*/  eg_timer; int /*<<< orphan*/  eg_cnt; int /*<<< orphan*/  addr_A1; int /*<<< orphan*/  status; int /*<<< orphan*/  address; int /*<<< orphan*/ * block_fnum_sl3; int /*<<< orphan*/ * block_fnum; int /*<<< orphan*/  volume; } ;
typedef  TYPE_6__ ym_save_addon_slot ;
typedef  TYPE_6__ ym_save_addon2 ;
typedef  TYPE_6__ ym_save_addon ;
typedef  int /*<<< orphan*/  sa2 ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_15__ {int /*<<< orphan*/  status; int /*<<< orphan*/  address; } ;
struct TYPE_14__ {int /*<<< orphan*/ * block_fnum; } ;
struct TYPE_16__ {int /*<<< orphan*/  lfo_cnt; int /*<<< orphan*/  eg_timer; int /*<<< orphan*/  eg_cnt; TYPE_4__ ST; TYPE_3__ SL3; } ;
struct TYPE_18__ {unsigned char* REGS; TYPE_5__ OPN; int /*<<< orphan*/  addr_A1; TYPE_2__* CH; } ;
struct TYPE_13__ {int /*<<< orphan*/  block_fnum; TYPE_1__* SLOT; } ;
struct TYPE_12__ {int state; int phase; scalar_t__ key; int /*<<< orphan*/  volume; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_lfo_ampm ; 
 int /*<<< orphan*/  memcpy (unsigned char*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 TYPE_9__ ym2612 ; 

void YM2612PicoStateSave2(int tat, int tbt)
{
	ym_save_addon_slot ss;
	ym_save_addon2 sa2;
	ym_save_addon sa;
	unsigned char *ptr;
	int c, s;

	memset(&sa, 0, sizeof(sa));
	memset(&sa2, 0, sizeof(sa2));

	// chans 1,2,3
	ptr = &ym2612.REGS[0x0b8];
	for (c = 0; c < 3; c++)
	{
		for (s = 0; s < 4; s++) {
			ss.state_phase = (ym2612.CH[c].SLOT[s].state << 29) | (ym2612.CH[c].SLOT[s].phase >> 3);
			ss.volume = ym2612.CH[c].SLOT[s].volume;
			if (ym2612.CH[c].SLOT[s].key)
				sa.keyon_field |= 1 << (c*4 + s);
			memcpy(ptr, &ss, 6);
			ptr += 6;
		}
		sa2.block_fnum[c] = ym2612.CH[c].block_fnum;
	}
	// chans 4,5,6
	ptr = &ym2612.REGS[0x1b8];
	for (; c < 6; c++)
	{
		for (s = 0; s < 4; s++) {
			ss.state_phase = (ym2612.CH[c].SLOT[s].state << 29) | (ym2612.CH[c].SLOT[s].phase >> 3);
			ss.volume = ym2612.CH[c].SLOT[s].volume;
			if (ym2612.CH[c].SLOT[s].key)
				sa.keyon_field |= 1 << (c*4 + s);
			memcpy(ptr, &ss, 6);
			ptr += 6;
		}
		sa2.block_fnum[c] = ym2612.CH[c].block_fnum;
	}
	for (c = 0; c < 3; c++)
	{
		sa2.block_fnum_sl3[c] = ym2612.OPN.SL3.block_fnum[c];
	}

	memcpy(&ym2612.REGS[0], &sa2, sizeof(sa2)); // 0x20 max

	// other things
	ptr = &ym2612.REGS[0x100];
	sa.magic = 0x41534d59; // 'YMSA'
	sa.address = ym2612.OPN.ST.address;
	sa.status  = ym2612.OPN.ST.status;
	sa.addr_A1 = ym2612.addr_A1;
	sa.TAT     = tat;
	sa.TBT     = tbt;
	sa.eg_cnt  = ym2612.OPN.eg_cnt;
	sa.eg_timer = ym2612.OPN.eg_timer;
	sa.lfo_cnt  = ym2612.OPN.lfo_cnt;
	sa.lfo_ampm = g_lfo_ampm;
	memcpy(ptr, &sa, sizeof(sa)); // 0x30 max
}