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
typedef  int u_int32_t ;
struct timeval {int dummy; } ;
struct TYPE_2__ {scalar_t__ rmx_expire; int /*<<< orphan*/  rmx_mtu; int /*<<< orphan*/  rmx_hopcount; int /*<<< orphan*/  rmx_rttvar; int /*<<< orphan*/  rmx_rtt; int /*<<< orphan*/  rmx_ssthresh; int /*<<< orphan*/  rmx_sendpipe; int /*<<< orphan*/  rmx_recvpipe; } ;
struct rtentry {scalar_t__ base_calendartime; scalar_t__ base_uptime; scalar_t__ rt_expire; int rt_flags; int /*<<< orphan*/  (* rt_llinfo_refresh ) (struct rtentry*) ;TYPE_1__ rt_rmx; } ;
struct rt_metrics {scalar_t__ rmx_expire; int /*<<< orphan*/  rmx_mtu; int /*<<< orphan*/  rmx_hopcount; int /*<<< orphan*/  rmx_rttvar; int /*<<< orphan*/  rmx_rtt; int /*<<< orphan*/  rmx_ssthresh; int /*<<< orphan*/  rmx_sendpipe; int /*<<< orphan*/  rmx_recvpipe; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 scalar_t__ NET_CALCULATE_CLOCKSKEW (struct timeval,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int RTF_LLINFO ; 
 int RTF_STATIC ; 
 int RTV_EXPIRE ; 
 int RTV_HOPCOUNT ; 
 int RTV_MTU ; 
 int RTV_REFRESH_HOST ; 
 int RTV_RPIPE ; 
 int RTV_RTT ; 
 int RTV_RTTVAR ; 
 int RTV_SPIPE ; 
 int RTV_SSTHRESH ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int /*<<< orphan*/  net_uptime () ; 
 int /*<<< orphan*/  rt_setexpire (struct rtentry*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct rtentry*) ; 

__attribute__((used)) static int
rt_setmetrics(u_int32_t which, struct rt_metrics *in, struct rtentry *out)
{
	if (!(which & RTV_REFRESH_HOST)) {
		struct timeval caltime;
		getmicrotime(&caltime);
#define	metric(f, e) if (which & (f)) out->rt_rmx.e = in->e;
		metric(RTV_RPIPE, rmx_recvpipe);
		metric(RTV_SPIPE, rmx_sendpipe);
		metric(RTV_SSTHRESH, rmx_ssthresh);
		metric(RTV_RTT, rmx_rtt);
		metric(RTV_RTTVAR, rmx_rttvar);
		metric(RTV_HOPCOUNT, rmx_hopcount);
		metric(RTV_MTU, rmx_mtu);
		metric(RTV_EXPIRE, rmx_expire);
#undef metric
		if (out->rt_rmx.rmx_expire > 0) {
			/* account for system time change */
			getmicrotime(&caltime);
			out->base_calendartime +=
				NET_CALCULATE_CLOCKSKEW(caltime,
						out->base_calendartime,
						net_uptime(), out->base_uptime);
			rt_setexpire(out,
					out->rt_rmx.rmx_expire -
					out->base_calendartime +
					out->base_uptime);
		} else {
			rt_setexpire(out, 0);
		}

		VERIFY(out->rt_expire == 0 || out->rt_rmx.rmx_expire != 0);
		VERIFY(out->rt_expire != 0 || out->rt_rmx.rmx_expire == 0);
	} else {
		/* Only RTV_REFRESH_HOST must be set */
		if ((which & ~RTV_REFRESH_HOST) ||
		    (out->rt_flags & RTF_STATIC) ||
		    !(out->rt_flags & RTF_LLINFO)) {
			return (EINVAL);
		}

		if (out->rt_llinfo_refresh == NULL) {
			return (ENOTSUP);
		}

		out->rt_llinfo_refresh(out);
	}
	return (0);
}