#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pack; scalar_t__ eg_timer; scalar_t__ eg_timer_add; unsigned int vol_out1; unsigned int vol_out2; unsigned int vol_out3; unsigned int vol_out4; int op1_out; int mem; int algo; scalar_t__ incr4; int /*<<< orphan*/  phase4; scalar_t__ incr3; int /*<<< orphan*/  phase3; scalar_t__ incr2; int /*<<< orphan*/  phase2; scalar_t__ incr1; int /*<<< orphan*/  phase1; TYPE_1__* CH; int /*<<< orphan*/  eg_cnt; scalar_t__ lfo_inc; scalar_t__ lfo_cnt; } ;
typedef  TYPE_2__ chan_rend_context ;
struct TYPE_7__ {scalar_t__ state; } ;
struct TYPE_5__ {int ALGO; TYPE_3__* SLOT; } ;

/* Variables and functions */
 scalar_t__ EG_OFF ; 
 scalar_t__ EG_TIMER_OVERFLOW ; 
 unsigned int ENV_QUIET ; 
 size_t SLOT1 ; 
 size_t SLOT2 ; 
 size_t SLOT3 ; 
 size_t SLOT4 ; 
 int advance_lfo (int,scalar_t__,scalar_t__) ; 
 int op_calc (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ op_calc1 (int /*<<< orphan*/ ,unsigned int,int) ; 
 void* update_eg_phase (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chan_render_loop(chan_rend_context *ct, int *buffer, int length)
{
	int scounter;					/* sample counter */

	/* sample generating loop */
	for (scounter = 0; scounter < length; scounter++)
	{
		int smp = 0;		/* produced sample */
		unsigned int eg_out, eg_out2, eg_out4;

		if (ct->pack & 8) { /* LFO enabled ? (test Earthworm Jim in between demo 1 and 2) */
			ct->pack = (ct->pack&0xffff) | (advance_lfo(ct->pack >> 16, ct->lfo_cnt, ct->lfo_cnt + ct->lfo_inc) << 16);
			ct->lfo_cnt += ct->lfo_inc;
		}

		ct->eg_timer += ct->eg_timer_add;
		while (ct->eg_timer >= EG_TIMER_OVERFLOW)
		{
			ct->eg_timer -= EG_TIMER_OVERFLOW;
			ct->eg_cnt++;

			if (ct->CH->SLOT[SLOT1].state != EG_OFF) ct->vol_out1 = update_eg_phase(&ct->CH->SLOT[SLOT1], ct->eg_cnt);
			if (ct->CH->SLOT[SLOT2].state != EG_OFF) ct->vol_out2 = update_eg_phase(&ct->CH->SLOT[SLOT2], ct->eg_cnt);
			if (ct->CH->SLOT[SLOT3].state != EG_OFF) ct->vol_out3 = update_eg_phase(&ct->CH->SLOT[SLOT3], ct->eg_cnt);
			if (ct->CH->SLOT[SLOT4].state != EG_OFF) ct->vol_out4 = update_eg_phase(&ct->CH->SLOT[SLOT4], ct->eg_cnt);
		}

		if (ct->pack & 4) continue; /* output disabled */

		/* calculate channel sample */
		eg_out = ct->vol_out1;
		if ( (ct->pack & 8) && (ct->pack&(1<<(SLOT1+8))) ) eg_out += ct->pack >> (((ct->pack&0xc0)>>6)+24);

		if( eg_out < ENV_QUIET )	/* SLOT 1 */
		{
			int out = 0;

			if (ct->pack&0xf000) out = ((ct->op1_out>>16) + ((ct->op1_out<<16)>>16)) << ((ct->pack&0xf000)>>12); /* op1_out0 + op1_out1 */
			ct->op1_out <<= 16;
			ct->op1_out |= (unsigned short)op_calc1(ct->phase1, eg_out, out);
		} else {
			ct->op1_out <<= 16; /* op1_out0 = op1_out1; op1_out1 = 0; */
		}

		eg_out  = ct->vol_out3; // volume_calc(&CH->SLOT[SLOT3]);
		eg_out2 = ct->vol_out2; // volume_calc(&CH->SLOT[SLOT2]);
		eg_out4 = ct->vol_out4; // volume_calc(&CH->SLOT[SLOT4]);

		if (ct->pack & 8) {
			unsigned int add = ct->pack >> (((ct->pack&0xc0)>>6)+24);
			if (ct->pack & (1<<(SLOT3+8))) eg_out  += add;
			if (ct->pack & (1<<(SLOT2+8))) eg_out2 += add;
			if (ct->pack & (1<<(SLOT4+8))) eg_out4 += add;
		}

		switch( ct->CH->ALGO )
		{
			case 0:
			{
				/* M1---C1---MEM---M2---C2---OUT */
				int m2,c1,c2=0;	/* Phase Modulation input for operators 2,3,4 */
				m2 = ct->mem;
				c1 = ct->op1_out>>16;
				if( eg_out  < ENV_QUIET ) {		/* SLOT 3 */
					c2  = op_calc(ct->phase3, eg_out,  m2);
				}
				if( eg_out2 < ENV_QUIET ) {		/* SLOT 2 */
					ct->mem = op_calc(ct->phase2, eg_out2, c1);
				}
				else ct->mem = 0;
				if( eg_out4 < ENV_QUIET ) {		/* SLOT 4 */
					smp = op_calc(ct->phase4, eg_out4, c2);
				}
				break;
			}
			case 1:
			{
				/* M1------+-MEM---M2---C2---OUT */
				/*      C1-+                     */
				int m2,c2=0;
				m2 = ct->mem;
				ct->mem = ct->op1_out>>16;
				if( eg_out  < ENV_QUIET ) {		/* SLOT 3 */
					c2  = op_calc(ct->phase3, eg_out,  m2);
				}
				if( eg_out2 < ENV_QUIET ) {		/* SLOT 2 */
					ct->mem+= op_calc(ct->phase2, eg_out2, 0);
				}
				if( eg_out4 < ENV_QUIET ) {		/* SLOT 4 */
					smp = op_calc(ct->phase4, eg_out4, c2);
				}
				break;
			}
			case 2:
			{
				/* M1-----------------+-C2---OUT */
				/*      C1---MEM---M2-+          */
				int m2,c2;
				m2 = ct->mem;
				c2 = ct->op1_out>>16;
				if( eg_out  < ENV_QUIET ) {		/* SLOT 3 */
					c2 += op_calc(ct->phase3, eg_out,  m2);
				}
				if( eg_out2 < ENV_QUIET ) {		/* SLOT 2 */
					ct->mem = op_calc(ct->phase2, eg_out2, 0);
				}
				else ct->mem = 0;
				if( eg_out4 < ENV_QUIET ) {		/* SLOT 4 */
					smp = op_calc(ct->phase4, eg_out4, c2);
				}
				break;
			}
			case 3:
			{
				/* M1---C1---MEM------+-C2---OUT */
				/*                 M2-+          */
				int c1,c2;
				c2 = ct->mem;
				c1 = ct->op1_out>>16;
				if( eg_out  < ENV_QUIET ) {		/* SLOT 3 */
					c2 += op_calc(ct->phase3, eg_out,  0);
				}
				if( eg_out2 < ENV_QUIET ) {		/* SLOT 2 */
					ct->mem = op_calc(ct->phase2, eg_out2, c1);
				}
				else ct->mem = 0;
				if( eg_out4 < ENV_QUIET ) {		/* SLOT 4 */
					smp = op_calc(ct->phase4, eg_out4, c2);
				}
				break;
			}
			case 4:
			{
				/* M1---C1-+-OUT */
				/* M2---C2-+     */
				/* MEM: not used */
				int c1,c2=0;
				c1 = ct->op1_out>>16;
				if( eg_out  < ENV_QUIET ) {		/* SLOT 3 */
					c2  = op_calc(ct->phase3, eg_out,  0);
				}
				if( eg_out2 < ENV_QUIET ) {		/* SLOT 2 */
					smp = op_calc(ct->phase2, eg_out2, c1);
				}
				if( eg_out4 < ENV_QUIET ) {		/* SLOT 4 */
					smp+= op_calc(ct->phase4, eg_out4, c2);
				}
				break;
			}
			case 5:
			{
				/*    +----C1----+     */
				/* M1-+-MEM---M2-+-OUT */
				/*    +----C2----+     */
				int m2,c1,c2;
				m2 = ct->mem;
				ct->mem = c1 = c2 = ct->op1_out>>16;
				if( eg_out < ENV_QUIET ) {		/* SLOT 3 */
					smp = op_calc(ct->phase3, eg_out, m2);
				}
				if( eg_out2 < ENV_QUIET ) {		/* SLOT 2 */
					smp+= op_calc(ct->phase2, eg_out2, c1);
				}
				if( eg_out4 < ENV_QUIET ) {		/* SLOT 4 */
					smp+= op_calc(ct->phase4, eg_out4, c2);
				}
				break;
			}
			case 6:
			{
				/* M1---C1-+     */
				/*      M2-+-OUT */
				/*      C2-+     */
				/* MEM: not used */
				int c1;
				c1 = ct->op1_out>>16;
				if( eg_out < ENV_QUIET ) {		/* SLOT 3 */
					smp = op_calc(ct->phase3, eg_out,  0);
				}
				if( eg_out2 < ENV_QUIET ) {		/* SLOT 2 */
					smp+= op_calc(ct->phase2, eg_out2, c1);
				}
				if( eg_out4 < ENV_QUIET ) {		/* SLOT 4 */
					smp+= op_calc(ct->phase4, eg_out4, 0);
				}
				break;
			}
			case 7:
			{
				/* M1-+     */
				/* C1-+-OUT */
				/* M2-+     */
				/* C2-+     */
				/* MEM: not used*/
				smp = ct->op1_out>>16;
				if( eg_out < ENV_QUIET ) {		/* SLOT 3 */
					smp += op_calc(ct->phase3, eg_out,  0);
				}
				if( eg_out2 < ENV_QUIET ) {		/* SLOT 2 */
					smp += op_calc(ct->phase2, eg_out2, 0);
				}
				if( eg_out4 < ENV_QUIET ) {		/* SLOT 4 */
					smp += op_calc(ct->phase4, eg_out4, 0);
				}
				break;
			}
		}
		/* done calculating channel sample */

		/* mix sample to output buffer */
		if (smp) {
			if (ct->pack & 1) { /* stereo */
				if (ct->pack & 0x20) /* L */ /* TODO: check correctness */
					buffer[scounter*2] += smp;
				if (ct->pack & 0x10) /* R */
					buffer[scounter*2+1] += smp;
			} else {
				buffer[scounter] += smp;
			}
			ct->algo = 8; // algo is only used in asm, here only bit3 is used
		}

		/* update phase counters AFTER output calculations */
		ct->phase1 += ct->incr1;
		ct->phase2 += ct->incr2;
		ct->phase3 += ct->incr3;
		ct->phase4 += ct->incr4;
	}
}