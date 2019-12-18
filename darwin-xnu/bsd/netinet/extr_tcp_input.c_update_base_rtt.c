#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  scalar_t__ u_int32_t ;
struct tcpcb {int t_flagsext; void* t_recv_throttle_ts; scalar_t__ t_rttcur; TYPE_2__* t_inpcb; } ;
struct rtentry {scalar_t__ rtt_expire_ts; scalar_t__ rtt_index; scalar_t__* rtt_hist; scalar_t__ rtt_min; } ;
struct TYPE_3__ {struct rtentry* ro_rt; } ;
struct TYPE_4__ {TYPE_1__ inp_route; } ;

/* Variables and functions */
 scalar_t__ NRTT_HIST ; 
 int /*<<< orphan*/  RT_LOCK_SPIN (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int TCP_RECV_THROTTLE_WIN ; 
 int TCP_RTT_HISTORY_EXPIRE_TIME ; 
 int TF_RECV_THROTTLE ; 
 void* min (scalar_t__,void*) ; 
 scalar_t__ target_qdelay ; 
 void* tcp_now ; 

void
update_base_rtt(struct tcpcb *tp, uint32_t rtt)
{
	u_int32_t base_rtt, i;
	struct rtentry *rt;

	if ((rt = tp->t_inpcb->inp_route.ro_rt) == NULL)
		return;
	if (rt->rtt_expire_ts == 0) {
		RT_LOCK_SPIN(rt);
		if (rt->rtt_expire_ts != 0) {
			RT_UNLOCK(rt);
			goto update;
		}
		rt->rtt_expire_ts = tcp_now;
		rt->rtt_index = 0;
		rt->rtt_hist[0] = rtt;
		rt->rtt_min = rtt;
		RT_UNLOCK(rt);
		return;
	}
update:
#if TRAFFIC_MGT
	/*
	 * If the recv side is being throttled, check if the
	 * current RTT is closer to the base RTT seen in
	 * first (recent) two slots. If so, unthrottle the stream.
	 */
	if ((tp->t_flagsext & TF_RECV_THROTTLE) &&
	    (int)(tcp_now - tp->t_recv_throttle_ts) >= TCP_RECV_THROTTLE_WIN) {
		base_rtt = rt->rtt_min;
		if (tp->t_rttcur <= (base_rtt + target_qdelay)) {
			tp->t_flagsext &= ~TF_RECV_THROTTLE;
			tp->t_recv_throttle_ts = 0;
		}
	}
#endif /* TRAFFIC_MGT */
	if ((int)(tcp_now - rt->rtt_expire_ts) >=
	    TCP_RTT_HISTORY_EXPIRE_TIME) {
		RT_LOCK_SPIN(rt);
		/* check the condition again to avoid race */
		if ((int)(tcp_now - rt->rtt_expire_ts) >=
		    TCP_RTT_HISTORY_EXPIRE_TIME) {
			rt->rtt_index++;
			if (rt->rtt_index >= NRTT_HIST)
				rt->rtt_index = 0;
			rt->rtt_hist[rt->rtt_index] = rtt;
			rt->rtt_expire_ts = tcp_now;
		} else {
			rt->rtt_hist[rt->rtt_index] =
			    min(rt->rtt_hist[rt->rtt_index], rtt);
		}
		/* forget the old value and update minimum */
		rt->rtt_min = 0;
		for (i = 0; i < NRTT_HIST; ++i) {
			if (rt->rtt_hist[i] != 0 &&
			    (rt->rtt_min == 0 ||
			    rt->rtt_hist[i] < rt->rtt_min))
				rt->rtt_min = rt->rtt_hist[i];
		}
		RT_UNLOCK(rt);
	} else {
		rt->rtt_hist[rt->rtt_index] =
		    min(rt->rtt_hist[rt->rtt_index], rtt);
		if (rt->rtt_min == 0)
			rt->rtt_min = rtt;
		else
			rt->rtt_min = min(rt->rtt_min, rtt);
	}
}