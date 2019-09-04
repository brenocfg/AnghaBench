#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct xtcpcb64 {int t_force; scalar_t__ t_badrxtwin; int /*<<< orphan*/  snd_ssthresh_prev; int /*<<< orphan*/  snd_cwnd_prev; int /*<<< orphan*/  snd_recover; scalar_t__ cc_recv; scalar_t__ cc_send; int /*<<< orphan*/  last_ack_sent; int /*<<< orphan*/  ts_recent_age; int /*<<< orphan*/  ts_recent; int /*<<< orphan*/  requested_s_scale; int /*<<< orphan*/  request_r_scale; int /*<<< orphan*/  rcv_scale; int /*<<< orphan*/  snd_scale; int /*<<< orphan*/  t_iobc; int /*<<< orphan*/  t_oobflags; int /*<<< orphan*/  t_softerror; int /*<<< orphan*/  max_sndwnd; int /*<<< orphan*/  t_rttupdated; int /*<<< orphan*/  t_rttmin; int /*<<< orphan*/  t_rxtshift; int /*<<< orphan*/  t_rttvar; int /*<<< orphan*/  t_srtt; int /*<<< orphan*/  t_maxseg; int /*<<< orphan*/  t_rxtcur; int /*<<< orphan*/  t_rtseq; int /*<<< orphan*/  t_rtttime; int /*<<< orphan*/  t_starttime; int /*<<< orphan*/  t_rcvtime; int /*<<< orphan*/  t_maxopd; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  rcv_up; int /*<<< orphan*/  rcv_wnd; int /*<<< orphan*/  rcv_adv; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  irs; int /*<<< orphan*/  iss; int /*<<< orphan*/  snd_wl2; int /*<<< orphan*/  snd_wl1; int /*<<< orphan*/  snd_up; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  snd_max; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  t_flags; int /*<<< orphan*/  t_state; int /*<<< orphan*/ * t_timer; int /*<<< orphan*/  t_dupacks; scalar_t__ t_segq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lh_first; } ;
struct tcpcb {int t_flagsext; int /*<<< orphan*/  snd_ssthresh_prev; int /*<<< orphan*/  snd_cwnd_prev; int /*<<< orphan*/  snd_recover; int /*<<< orphan*/  last_ack_sent; int /*<<< orphan*/  ts_recent_age; int /*<<< orphan*/  ts_recent; int /*<<< orphan*/  requested_s_scale; int /*<<< orphan*/  request_r_scale; int /*<<< orphan*/  rcv_scale; int /*<<< orphan*/  snd_scale; int /*<<< orphan*/  t_iobc; int /*<<< orphan*/  t_oobflags; int /*<<< orphan*/  t_softerror; int /*<<< orphan*/  max_sndwnd; int /*<<< orphan*/  t_rttupdated; int /*<<< orphan*/  t_rttmin; int /*<<< orphan*/  t_rxtshift; int /*<<< orphan*/  t_rttvar; int /*<<< orphan*/  t_srtt; int /*<<< orphan*/  t_maxseg; int /*<<< orphan*/  t_rxtcur; int /*<<< orphan*/  t_rtseq; int /*<<< orphan*/  t_rtttime; int /*<<< orphan*/  t_starttime; int /*<<< orphan*/  t_rcvtime; int /*<<< orphan*/  t_maxopd; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  rcv_up; int /*<<< orphan*/  rcv_wnd; int /*<<< orphan*/  rcv_adv; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  irs; int /*<<< orphan*/  iss; int /*<<< orphan*/  snd_wl2; int /*<<< orphan*/  snd_wl1; int /*<<< orphan*/  snd_up; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  snd_max; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  t_flags; int /*<<< orphan*/  t_state; int /*<<< orphan*/ * t_timer; int /*<<< orphan*/  t_dupacks; TYPE_1__ t_segq; } ;

/* Variables and functions */
 size_t TCPT_2MSL ; 
 size_t TCPT_2MSL_EXT ; 
 size_t TCPT_KEEP ; 
 size_t TCPT_KEEP_EXT ; 
 size_t TCPT_PERSIST ; 
 size_t TCPT_PERSIST_EXT ; 
 size_t TCPT_REXMT ; 
 size_t TCPT_REXMT_EXT ; 
 int TF_FORCE ; 
 scalar_t__ VM_KERNEL_ADDRPERM (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcpcb_to_xtcpcb64(struct tcpcb *tp, struct xtcpcb64 *otp)
{
	otp->t_segq = (uint32_t)VM_KERNEL_ADDRPERM(tp->t_segq.lh_first);
	otp->t_dupacks = tp->t_dupacks;
	otp->t_timer[TCPT_REXMT_EXT] = tp->t_timer[TCPT_REXMT];
	otp->t_timer[TCPT_PERSIST_EXT] = tp->t_timer[TCPT_PERSIST];
	otp->t_timer[TCPT_KEEP_EXT] = tp->t_timer[TCPT_KEEP];
	otp->t_timer[TCPT_2MSL_EXT] = tp->t_timer[TCPT_2MSL];
	otp->t_state = tp->t_state;
	otp->t_flags = tp->t_flags;
	otp->t_force = (tp->t_flagsext & TF_FORCE) ? 1 : 0;
	otp->snd_una = tp->snd_una;
	otp->snd_max = tp->snd_max;
	otp->snd_nxt = tp->snd_nxt;
	otp->snd_up = tp->snd_up;
	otp->snd_wl1 = tp->snd_wl1;
	otp->snd_wl2 = tp->snd_wl2;
	otp->iss = tp->iss;
	otp->irs = tp->irs;
	otp->rcv_nxt = tp->rcv_nxt;
	otp->rcv_adv = tp->rcv_adv;
	otp->rcv_wnd = tp->rcv_wnd;
	otp->rcv_up = tp->rcv_up;
	otp->snd_wnd = tp->snd_wnd;
	otp->snd_cwnd = tp->snd_cwnd;
	otp->snd_ssthresh = tp->snd_ssthresh;
	otp->t_maxopd = tp->t_maxopd;
	otp->t_rcvtime = tp->t_rcvtime;
	otp->t_starttime = tp->t_starttime;
	otp->t_rtttime = tp->t_rtttime;
	otp->t_rtseq = tp->t_rtseq;
	otp->t_rxtcur = tp->t_rxtcur;
	otp->t_maxseg = tp->t_maxseg;
	otp->t_srtt = tp->t_srtt;
	otp->t_rttvar = tp->t_rttvar;
	otp->t_rxtshift = tp->t_rxtshift;
	otp->t_rttmin = tp->t_rttmin;
	otp->t_rttupdated = tp->t_rttupdated;
	otp->max_sndwnd = tp->max_sndwnd;
	otp->t_softerror = tp->t_softerror;
	otp->t_oobflags = tp->t_oobflags;
	otp->t_iobc = tp->t_iobc;
	otp->snd_scale = tp->snd_scale;
	otp->rcv_scale = tp->rcv_scale;
	otp->request_r_scale = tp->request_r_scale;
	otp->requested_s_scale = tp->requested_s_scale;
	otp->ts_recent = tp->ts_recent;
	otp->ts_recent_age = tp->ts_recent_age;
	otp->last_ack_sent = tp->last_ack_sent;
	otp->cc_send = 0;
	otp->cc_recv = 0;
	otp->snd_recover = tp->snd_recover;
	otp->snd_cwnd_prev = tp->snd_cwnd_prev;
	otp->snd_ssthresh_prev = tp->snd_ssthresh_prev;
	otp->t_badrxtwin = 0;
}