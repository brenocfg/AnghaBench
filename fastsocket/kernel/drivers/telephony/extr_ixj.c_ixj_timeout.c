#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_33__ {int hookstate; scalar_t__ dtmf_ready; } ;
struct TYPE_35__ {scalar_t__ bytes; TYPE_4__ bits; } ;
struct TYPE_34__ {int firstring; int cidring; int cidsent; scalar_t__ pstn_present; int /*<<< orphan*/  pstncheck; int /*<<< orphan*/  ringing; scalar_t__ cringing; scalar_t__ ringback; scalar_t__ busytone; scalar_t__ dialtone; } ;
struct TYPE_32__ {int high; int low; } ;
struct TYPE_31__ {int low; } ;
struct TYPE_36__ {int board; int hookstate; int tone_state; int m_hook; int tone_on_time; int tone_off_time; int ring_cadence_t; int ring_cadence; int proc_load; scalar_t__ cardtype; int /*<<< orphan*/  busyflags; int /*<<< orphan*/  poll_q; TYPE_6__ ex; TYPE_5__ flags; scalar_t__ dtmf_rp; scalar_t__ dtmf_wp; TYPE_3__ ssr; TYPE_2__ dsp; TYPE_1__* cadence_f; void* ring_cadence_jif; scalar_t__ fskdcnt; int /*<<< orphan*/  tone_index; void* tone_start_jif; int /*<<< orphan*/  timerchecks; int /*<<< orphan*/  DSPWrite; scalar_t__ DSPbase; } ;
struct TYPE_30__ {int state; int on1; int off1; int on2; int off2; int on3; int off3; scalar_t__ en_filter; void* off3dot; void* on3dot; void* off2dot; void* on2dot; void* off1dot; void* on1dot; scalar_t__ enable; } ;
typedef  TYPE_7__ IXJ ;

/* Variables and functions */
 scalar_t__ IsRxReady (TYPE_7__*) ; 
 scalar_t__ IsTxReady (TYPE_7__*) ; 
 int /*<<< orphan*/  LineMonitor (TYPE_7__*) ; 
 scalar_t__ PLD_SLIC_STATE_ACTIVE ; 
 scalar_t__ PLD_SLIC_STATE_OHT ; 
 int /*<<< orphan*/  POLL_IN ; 
 scalar_t__ QTI_LINEJACK ; 
 int /*<<< orphan*/  SIG_HOOKSTATE ; 
 scalar_t__ SLIC_GetState (TYPE_7__*) ; 
 int /*<<< orphan*/  SLIC_SetState (scalar_t__,TYPE_7__*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int hertz ; 
 int /*<<< orphan*/  ixj_WriteDSPCommand (int,TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_add_timer (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_busytone (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_cpt_stop (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_dialtone (TYPE_7__*) ; 
 int ixj_hookstate (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_kill_fasync (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixj_perfmon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixj_play_tone (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixj_pre_cid (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_pstn_state (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_read_frame (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_ring_off (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_ring_on (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_ringback (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_tone_timeout (TYPE_7__*) ; 
 int /*<<< orphan*/  ixj_write_frame (TYPE_7__*) ; 
 int ixjdebug ; 
 void* jiffies ; 
 int /*<<< orphan*/  printk (char*,int,void*) ; 
 int /*<<< orphan*/  read_filters (TYPE_7__*) ; 
 scalar_t__ test_and_set_bit (int,void*) ; 
 scalar_t__ time_after (void*,void*) ; 
 scalar_t__ time_before (void*,void*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixj_timeout(unsigned long ptr)
{
	int board;
	unsigned long jifon;
	IXJ *j = (IXJ *)ptr;
	board = j->board;

	if (j->DSPbase && atomic_read(&j->DSPWrite) == 0 && test_and_set_bit(board, (void *)&j->busyflags) == 0) {
		ixj_perfmon(j->timerchecks);
		j->hookstate = ixj_hookstate(j);
		if (j->tone_state) {
			if (!(j->hookstate)) {
				ixj_cpt_stop(j);
				if (j->m_hook) {
					j->m_hook = 0;
					j->ex.bits.hookstate = 1;
					ixj_kill_fasync(j, SIG_HOOKSTATE, POLL_IN);
				}
				clear_bit(board, &j->busyflags);
				ixj_add_timer(j);
				return;
			}
			if (j->tone_state == 1)
				jifon = ((hertz * j->tone_on_time) * 25 / 100000);
			else
				jifon = ((hertz * j->tone_on_time) * 25 / 100000) + ((hertz * j->tone_off_time) * 25 / 100000);
			if (time_before(jiffies, j->tone_start_jif + jifon)) {
				if (j->tone_state == 1) {
					ixj_play_tone(j, j->tone_index);
					if (j->dsp.low == 0x20) {
						clear_bit(board, &j->busyflags);
						ixj_add_timer(j);
						return;
					}
				} else {
					ixj_play_tone(j, 0);
					if (j->dsp.low == 0x20) {
						clear_bit(board, &j->busyflags);
						ixj_add_timer(j);
						return;
					}
				}
			} else {
				ixj_tone_timeout(j);
				if (j->flags.dialtone) {
					ixj_dialtone(j);
				}
				if (j->flags.busytone) {
					ixj_busytone(j);
					if (j->dsp.low == 0x20) {
						clear_bit(board, &j->busyflags);
						ixj_add_timer(j);
						return;
					}
				}
				if (j->flags.ringback) {
					ixj_ringback(j);
					if (j->dsp.low == 0x20) {
						clear_bit(board, &j->busyflags);
						ixj_add_timer(j);
						return;
					}
				}
				if (!j->tone_state) {
					ixj_cpt_stop(j);
				}
			}
		}
		if (!(j->tone_state && j->dsp.low == 0x20)) {
			if (IsRxReady(j)) {
				ixj_read_frame(j);
			}
			if (IsTxReady(j)) {
				ixj_write_frame(j);
			}
		}
		if (j->flags.cringing) {
			if (j->hookstate & 1) {
				j->flags.cringing = 0;
				ixj_ring_off(j);
			} else if(j->cadence_f[5].enable && ((!j->cadence_f[5].en_filter) || (j->cadence_f[5].en_filter && j->flags.firstring))) {
				switch(j->cadence_f[5].state) {
					case 0:
						j->cadence_f[5].on1dot = jiffies + (long)((j->cadence_f[5].on1 * (hertz * 100) / 10000));
						if (time_before(jiffies, j->cadence_f[5].on1dot)) {
							if(ixjdebug & 0x0004) {
								printk("Ringing cadence state = %d - %ld\n", j->cadence_f[5].state, jiffies);
							}
							ixj_ring_on(j);
						}
						j->cadence_f[5].state = 1;
						break;
					case 1:
						if (time_after(jiffies, j->cadence_f[5].on1dot)) {
							j->cadence_f[5].off1dot = jiffies + (long)((j->cadence_f[5].off1 * (hertz * 100) / 10000));
							if(ixjdebug & 0x0004) {
								printk("Ringing cadence state = %d - %ld\n", j->cadence_f[5].state, jiffies);
							}
							ixj_ring_off(j);
							j->cadence_f[5].state = 2;
						}
						break;
					case 2:
						if (time_after(jiffies, j->cadence_f[5].off1dot)) {
							if(ixjdebug & 0x0004) {
								printk("Ringing cadence state = %d - %ld\n", j->cadence_f[5].state, jiffies);
							}
							ixj_ring_on(j);
							if (j->cadence_f[5].on2) {
								j->cadence_f[5].on2dot = jiffies + (long)((j->cadence_f[5].on2 * (hertz * 100) / 10000));
								j->cadence_f[5].state = 3;
							} else {
								j->cadence_f[5].state = 7;
							}
						}
						break;
					case 3:
						if (time_after(jiffies, j->cadence_f[5].on2dot)) {
							if(ixjdebug & 0x0004) {
								printk("Ringing cadence state = %d - %ld\n", j->cadence_f[5].state, jiffies);
							}
							ixj_ring_off(j);
							if (j->cadence_f[5].off2) {
								j->cadence_f[5].off2dot = jiffies + (long)((j->cadence_f[5].off2 * (hertz * 100) / 10000));
								j->cadence_f[5].state = 4;
							} else {
								j->cadence_f[5].state = 7;
							}
						}
						break;
					case 4:
						if (time_after(jiffies, j->cadence_f[5].off2dot)) {
							if(ixjdebug & 0x0004) {
								printk("Ringing cadence state = %d - %ld\n", j->cadence_f[5].state, jiffies);
							}
							ixj_ring_on(j);
							if (j->cadence_f[5].on3) {
								j->cadence_f[5].on3dot = jiffies + (long)((j->cadence_f[5].on3 * (hertz * 100) / 10000));
								j->cadence_f[5].state = 5;
							} else {
								j->cadence_f[5].state = 7;
							}
						}
						break;
					case 5:
						if (time_after(jiffies, j->cadence_f[5].on3dot)) {
							if(ixjdebug & 0x0004) {
								printk("Ringing cadence state = %d - %ld\n", j->cadence_f[5].state, jiffies);
							}
							ixj_ring_off(j);
							if (j->cadence_f[5].off3) {
								j->cadence_f[5].off3dot = jiffies + (long)((j->cadence_f[5].off3 * (hertz * 100) / 10000));
								j->cadence_f[5].state = 6;
							} else {
								j->cadence_f[5].state = 7;
							}
						}
						break;
					case 6:
						if (time_after(jiffies, j->cadence_f[5].off3dot)) {
							if(ixjdebug & 0x0004) {
								printk("Ringing cadence state = %d - %ld\n", j->cadence_f[5].state, jiffies);
							}
							j->cadence_f[5].state = 7;
						}
						break;
					case 7:
						if(ixjdebug & 0x0004) {
							printk("Ringing cadence state = %d - %ld\n", j->cadence_f[5].state, jiffies);
						}
						j->flags.cidring = 1;
						j->cadence_f[5].state = 0;
						break;
				}
				if (j->flags.cidring && !j->flags.cidsent) {
					j->flags.cidsent = 1;
					if(j->fskdcnt) {
						SLIC_SetState(PLD_SLIC_STATE_OHT, j);
						ixj_pre_cid(j);
					}
					j->flags.cidring = 0;
				}
				clear_bit(board, &j->busyflags);
				ixj_add_timer(j);
				return;
			} else {
				if (time_after(jiffies, j->ring_cadence_jif + (hertz / 2))) {
					if (j->flags.cidring && !j->flags.cidsent) {
						j->flags.cidsent = 1;
						if(j->fskdcnt) {
							SLIC_SetState(PLD_SLIC_STATE_OHT, j);
							ixj_pre_cid(j);
						}
						j->flags.cidring = 0;
					}
					j->ring_cadence_t--;
					if (j->ring_cadence_t == -1)
						j->ring_cadence_t = 15;
					j->ring_cadence_jif = jiffies;

					if (j->ring_cadence & 1 << j->ring_cadence_t) {
						if(j->flags.cidsent && j->cadence_f[5].en_filter)
							j->flags.firstring = 1;
						else
							ixj_ring_on(j);
					} else {
						ixj_ring_off(j);
						if(!j->flags.cidsent)
							j->flags.cidring = 1;
					}
				}
				clear_bit(board, &j->busyflags);
				ixj_add_timer(j);
				return;
			}
		}
		if (!j->flags.ringing) {
			if (j->hookstate) { /* & 1) { */
				if (j->dsp.low != 0x20 &&
				    SLIC_GetState(j) != PLD_SLIC_STATE_ACTIVE) {
					SLIC_SetState(PLD_SLIC_STATE_ACTIVE, j);
				}
				LineMonitor(j);
				read_filters(j);
				ixj_WriteDSPCommand(0x511B, j);
				j->proc_load = j->ssr.high << 8 | j->ssr.low;
				if (!j->m_hook && (j->hookstate & 1)) {
					j->m_hook = j->ex.bits.hookstate = 1;
					ixj_kill_fasync(j, SIG_HOOKSTATE, POLL_IN);
				}
			} else {
				if (j->ex.bits.dtmf_ready) {
					j->dtmf_wp = j->dtmf_rp = j->ex.bits.dtmf_ready = 0;
				}
				if (j->m_hook) {
					j->m_hook = 0;
					j->ex.bits.hookstate = 1;
					ixj_kill_fasync(j, SIG_HOOKSTATE, POLL_IN);
				}
			}
		}
		if (j->cardtype == QTI_LINEJACK && !j->flags.pstncheck && j->flags.pstn_present) {
			ixj_pstn_state(j);
		}
		if (j->ex.bytes) {
			wake_up_interruptible(&j->poll_q);	/* Wake any blocked selects */
		}
		clear_bit(board, &j->busyflags);
	}
	ixj_add_timer(j);
}