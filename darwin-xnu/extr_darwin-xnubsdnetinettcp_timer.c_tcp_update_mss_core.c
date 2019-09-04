#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct tcpcb {scalar_t__ t_maxopd; scalar_t__ t_maxseg; scalar_t__ t_cached_maxopd; } ;
struct ifnet {TYPE_4__* if_link_status; } ;
struct if_cellular_status_v1 {int valid_bitmask; scalar_t__ mss_recommended; } ;
struct TYPE_10__ {int /*<<< orphan*/  tcps_mss_to_low; int /*<<< orphan*/  tcps_mss_to_medium; int /*<<< orphan*/  tcps_mss_to_default; } ;
struct TYPE_6__ {struct if_cellular_status_v1 if_status_v1; } ;
struct TYPE_7__ {TYPE_1__ if_cell_u; } ;
struct TYPE_8__ {TYPE_2__ ifsr_cell; } ;
struct TYPE_9__ {TYPE_3__ ifsr_u; } ;

/* Variables and functions */
 scalar_t__ IF_CELL_UL_MSS_RECOMMENDED_LOW ; 
 scalar_t__ IF_CELL_UL_MSS_RECOMMENDED_MEDIUM ; 
 scalar_t__ IF_CELL_UL_MSS_RECOMMENDED_NONE ; 
 int IF_CELL_UL_MSS_RECOMMENDED_VALID ; 
 scalar_t__ tcp_mss_rec_low ; 
 scalar_t__ tcp_mss_rec_medium ; 
 TYPE_5__ tcpstat ; 

inline void
tcp_update_mss_core(struct tcpcb *tp, struct ifnet *ifp)
{
	struct if_cellular_status_v1 *ifsr;
	u_int32_t optlen;
	ifsr = &ifp->if_link_status->ifsr_u.ifsr_cell.if_cell_u.if_status_v1;
	if (ifsr->valid_bitmask & IF_CELL_UL_MSS_RECOMMENDED_VALID) {
		optlen = tp->t_maxopd - tp->t_maxseg;

		if (ifsr->mss_recommended ==
		    IF_CELL_UL_MSS_RECOMMENDED_NONE &&
		    tp->t_cached_maxopd > 0 &&
		    tp->t_maxopd < tp->t_cached_maxopd) {
			tp->t_maxopd = tp->t_cached_maxopd;
			tcpstat.tcps_mss_to_default++;
		} else if (ifsr->mss_recommended ==
		    IF_CELL_UL_MSS_RECOMMENDED_MEDIUM &&
		    tp->t_maxopd > tcp_mss_rec_medium) {
			tp->t_cached_maxopd = tp->t_maxopd;
			tp->t_maxopd = tcp_mss_rec_medium;
			tcpstat.tcps_mss_to_medium++;
		} else if (ifsr->mss_recommended ==
		    IF_CELL_UL_MSS_RECOMMENDED_LOW &&
		    tp->t_maxopd > tcp_mss_rec_low) {
			tp->t_cached_maxopd = tp->t_maxopd;
			tp->t_maxopd = tcp_mss_rec_low;
			tcpstat.tcps_mss_to_low++;
		}
		tp->t_maxseg = tp->t_maxopd - optlen;

		/*
		 * clear the cached value if it is same as the current
		 */
		if (tp->t_maxopd == tp->t_cached_maxopd)
			tp->t_cached_maxopd = 0;
	}
}