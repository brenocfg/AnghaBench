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
struct TYPE_6__ {int TBL; int TAL; scalar_t__ TA; scalar_t__ TB; scalar_t__ TBC; scalar_t__ TAC; } ;
struct TYPE_5__ {scalar_t__ key_csm; } ;
struct TYPE_7__ {int LFO_AM; TYPE_2__ ST; TYPE_1__ SL3; scalar_t__ LFO_PM; scalar_t__ lfo_cnt; scalar_t__ lfo_timer; scalar_t__ lfo_timer_overflow; scalar_t__ eg_cnt; scalar_t__ eg_timer; } ;
struct TYPE_8__ {int /*<<< orphan*/ * CH; TYPE_3__ OPN; scalar_t__ dacout; scalar_t__ dacen; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPNWriteReg (int,int) ; 
 int /*<<< orphan*/  reset_channels (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_timers (int) ; 
 TYPE_4__ ym2612 ; 

void YM2612ResetChip(void)
{
  int i;

  ym2612.OPN.eg_timer     = 0;
  ym2612.OPN.eg_cnt       = 0;

  ym2612.OPN.lfo_timer_overflow = 0;
  ym2612.OPN.lfo_timer          = 0;
  ym2612.OPN.lfo_cnt            = 0;
  ym2612.OPN.LFO_AM             = 126;
  ym2612.OPN.LFO_PM             = 0;

  ym2612.OPN.ST.TAC       = 0;
  ym2612.OPN.ST.TBC       = 0;

  ym2612.OPN.SL3.key_csm  = 0;

  ym2612.dacen            = 0;
  ym2612.dacout           = 0;
 
  set_timers(0x30);
  ym2612.OPN.ST.TB = 0;
  ym2612.OPN.ST.TBL = 256 << 4;
  ym2612.OPN.ST.TA = 0;
  ym2612.OPN.ST.TAL = 1024;

  reset_channels(&ym2612.CH[0] , 6 );

  for(i = 0xb6 ; i >= 0xb4 ; i-- )
  {
    OPNWriteReg(i      ,0xc0);
    OPNWriteReg(i|0x100,0xc0);
  }
  for(i = 0xb2 ; i >= 0x30 ; i-- )
  {
    OPNWriteReg(i      ,0);
    OPNWriteReg(i|0x100,0);
  }
}