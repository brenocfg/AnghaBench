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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ rcv_tsval; scalar_t__ rcv_tsecr; } ;
struct tcp_sock {TYPE_1__ rx_opt; } ;
struct sock {int dummy; } ;
struct lp {int remote_hz; scalar_t__ remote_ref_time; scalar_t__ local_ref_time; int /*<<< orphan*/  flag; } ;
typedef  int s64 ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LP_VALID_RHZ ; 
 struct lp* inet_csk_ca (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 tcp_lp_remote_hz_estimator(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct lp *lp = inet_csk_ca(sk);
	s64 rhz = lp->remote_hz << 6;	/* remote HZ << 6 */
	s64 m = 0;

	/* not yet record reference time
	 * go away!! record it before come back!! */
	if (lp->remote_ref_time == 0 || lp->local_ref_time == 0)
		goto out;

	/* we can't calc remote HZ with no different!! */
	if (tp->rx_opt.rcv_tsval == lp->remote_ref_time
	    || tp->rx_opt.rcv_tsecr == lp->local_ref_time)
		goto out;

	m = HZ * (tp->rx_opt.rcv_tsval -
		  lp->remote_ref_time) / (tp->rx_opt.rcv_tsecr -
					  lp->local_ref_time);
	if (m < 0)
		m = -m;

	if (rhz > 0) {
		m -= rhz >> 6;	/* m is now error in remote HZ est */
		rhz += m;	/* 63/64 old + 1/64 new */
	} else
		rhz = m << 6;

 out:
	/* record time for successful remote HZ calc */
	if ((rhz >> 6) > 0)
		lp->flag |= LP_VALID_RHZ;
	else
		lp->flag &= ~LP_VALID_RHZ;

	/* record reference time stamp */
	lp->remote_ref_time = tp->rx_opt.rcv_tsval;
	lp->local_ref_time = tp->rx_opt.rcv_tsecr;

	return rhz >> 6;
}