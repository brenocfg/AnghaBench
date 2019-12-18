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
typedef  int UINT8 ;
struct TYPE_4__ {unsigned int address; int TA; int TAC; unsigned int TB; int TBC; int /*<<< orphan*/  TBT; int /*<<< orphan*/  TAT; } ;
struct TYPE_5__ {TYPE_1__ ST; int /*<<< orphan*/  lfo_inc; int /*<<< orphan*/ * lfo_freq; } ;
struct TYPE_6__ {int addr_A1; int dacout; unsigned int dacen; TYPE_2__ OPN; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_KEYOFF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_KEYON (int,int /*<<< orphan*/ ) ; 
 int OPNWriteReg (int,unsigned int) ; 
 int /*<<< orphan*/  SLOT1 ; 
 int /*<<< orphan*/  SLOT2 ; 
 int /*<<< orphan*/  SLOT3 ; 
 int /*<<< orphan*/  SLOT4 ; 
 int /*<<< orphan*/  set_timers (unsigned int) ; 
 TYPE_3__ ym2612 ; 

int YM2612Write_(unsigned int a, unsigned int v)
{
	int addr, ret=1;

	v &= 0xff;	/* adjust to 8 bit bus */

	switch( a&3){
	case 0:	/* address port 0 */
		ym2612.OPN.ST.address = v;
		ym2612.addr_A1 = 0;
		ret=0;
		break;

	case 1:	/* data port 0    */
		if (ym2612.addr_A1 != 0) {
			ret=0;
			break;	/* verified on real YM2608 */
		}

		addr = ym2612.OPN.ST.address;

		switch( addr & 0xf0 )
		{
		case 0x20:	/* 0x20-0x2f Mode */
			switch( addr )
			{
			case 0x22:	/* LFO FREQ (YM2608/YM2610/YM2610B/YM2612) */
				if (v&0x08) /* LFO enabled ? */
				{
					ym2612.OPN.lfo_inc = ym2612.OPN.lfo_freq[v&7];
				}
				else
				{
					ym2612.OPN.lfo_inc = 0;
				}
				break;
#if 0 // handled elsewhere
			case 0x24: { // timer A High 8
					int TAnew = (ym2612.OPN.ST.TA & 0x03)|(((int)v)<<2);
					if(ym2612.OPN.ST.TA != TAnew) {
						// we should reset ticker only if new value is written. Outrun requires this.
						ym2612.OPN.ST.TA = TAnew;
						ym2612.OPN.ST.TAC = (1024-TAnew)*18;
						ym2612.OPN.ST.TAT = 0;
					}
				}
				ret=0;
				break;
			case 0x25: { // timer A Low 2
					int TAnew = (ym2612.OPN.ST.TA & 0x3fc)|(v&3);
					if(ym2612.OPN.ST.TA != TAnew) {
						ym2612.OPN.ST.TA = TAnew;
						ym2612.OPN.ST.TAC = (1024-TAnew)*18;
						ym2612.OPN.ST.TAT = 0;
					}
				}
				ret=0;
				break;
			case 0x26: // timer B
				if(ym2612.OPN.ST.TB != v) {
					ym2612.OPN.ST.TB = v;
					ym2612.OPN.ST.TBC  = (256-v)<<4;
					ym2612.OPN.ST.TBC *= 18;
					ym2612.OPN.ST.TBT  = 0;
				}
				ret=0;
				break;
#endif
			case 0x27:	/* mode, timer control */
				set_timers( v );
				ret=0;
				break;
			case 0x28:	/* key on / off */
				{
					UINT8 c;

					c = v & 0x03;
					if( c == 3 ) { ret=0; break; }
					if( v&0x04 ) c+=3;
					if(v&0x10) FM_KEYON(c,SLOT1); else FM_KEYOFF(c,SLOT1);
					if(v&0x20) FM_KEYON(c,SLOT2); else FM_KEYOFF(c,SLOT2);
					if(v&0x40) FM_KEYON(c,SLOT3); else FM_KEYOFF(c,SLOT3);
					if(v&0x80) FM_KEYON(c,SLOT4); else FM_KEYOFF(c,SLOT4);
					break;
				}
			case 0x2a:	/* DAC data (YM2612) */
				ym2612.dacout = ((int)v - 0x80) << 6;	/* level unknown (notaz: 8 seems to be too much) */
				ret=0;
				break;
			case 0x2b:	/* DAC Sel  (YM2612) */
				/* b7 = dac enable */
				ym2612.dacen = v & 0x80;
				ret=0;
				break;
			default:
				break;
			}
			break;
		default:	/* 0x30-0xff OPN section */
			/* write register */
			ret = OPNWriteReg(addr,v);
		}
		break;

	case 2:	/* address port 1 */
		ym2612.OPN.ST.address = v;
		ym2612.addr_A1 = 1;
		ret=0;
		break;

	case 3:	/* data port 1    */
		if (ym2612.addr_A1 != 1) {
			ret=0;
			break;	/* verified on real YM2608 */
		}

		addr = ym2612.OPN.ST.address | 0x100;

		ret = OPNWriteReg(addr, v);
		break;
	}

	return ret;
}