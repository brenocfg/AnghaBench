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
struct tcp_heuristics_head {int dummy; } ;
struct tcp_heuristic {scalar_t__ th_tfo_data_loss; scalar_t__ th_tfo_req_loss; scalar_t__ th_tfo_data_rst; scalar_t__ th_tfo_req_rst; scalar_t__ th_ecn_loss; scalar_t__ th_mptcp_loss; scalar_t__ th_ecn_droprst; scalar_t__ th_ecn_droprxmt; scalar_t__ th_ecn_synrst; void* th_ecn_backoff; void* th_mptcp_backoff; } ;
struct tcp_cache_key_src {int /*<<< orphan*/  af; int /*<<< orphan*/  ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_ecn_fallback_synrst; int /*<<< orphan*/  tcps_ecn_fallback_droprxmt; int /*<<< orphan*/  tcps_ecn_fallback_droprst; int /*<<< orphan*/  tcps_ecn_fallback_synloss; } ;

/* Variables and functions */
 scalar_t__ ECN_MAX_DROPRST ; 
 scalar_t__ ECN_MAX_DROPRXMT ; 
 scalar_t__ ECN_MAX_SYNRST ; 
 scalar_t__ ECN_MAX_SYN_LOSS ; 
 scalar_t__ MPTCP_MAX_SYN_LOSS ; 
 int TCPCACHE_F_ECN ; 
 int TCPCACHE_F_ECN_DROPRST ; 
 int TCPCACHE_F_ECN_DROPRXMT ; 
 int TCPCACHE_F_ECN_SYNRST ; 
 int TCPCACHE_F_MPTCP ; 
 int TCPCACHE_F_TFO_DATA ; 
 int TCPCACHE_F_TFO_DATA_RST ; 
 int TCPCACHE_F_TFO_REQ ; 
 int TCPCACHE_F_TFO_REQ_RST ; 
 int /*<<< orphan*/  TCP_CACHE_INC_IFNET_STAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_CACHE_OVERFLOW_PROTECT ; 
 scalar_t__ TFO_MAX_COOKIE_LOSS ; 
 int /*<<< orphan*/  __tcp_heuristic_tfo_middlebox_common (struct tcp_heuristic*) ; 
 int /*<<< orphan*/  ecn_fallback_droprst ; 
 int /*<<< orphan*/  ecn_fallback_droprxmt ; 
 int /*<<< orphan*/  ecn_fallback_synloss ; 
 int /*<<< orphan*/  ecn_fallback_synrst ; 
 int /*<<< orphan*/  tcp_ecn_timeout ; 
 struct tcp_heuristic* tcp_getheuristic_with_lock (struct tcp_cache_key_src*,int,struct tcp_heuristics_head**) ; 
 int /*<<< orphan*/  tcp_heuristic_unlock (struct tcp_heuristics_head*) ; 
 scalar_t__ tcp_min_to_hz (int /*<<< orphan*/ ) ; 
 void* tcp_now ; 
 TYPE_1__ tcpstat ; 

__attribute__((used)) static void tcp_heuristic_inc_counters(struct tcp_cache_key_src *tcks,
    u_int32_t flags)
{
	struct tcp_heuristics_head *head;
	struct tcp_heuristic *tpheur;

	tpheur = tcp_getheuristic_with_lock(tcks, 1, &head);
	if (tpheur == NULL)
		return;

	/* Limit to prevent integer-overflow during exponential backoff */
	if ((flags & TCPCACHE_F_TFO_DATA) && tpheur->th_tfo_data_loss < TCP_CACHE_OVERFLOW_PROTECT) {
		tpheur->th_tfo_data_loss++;

		if (tpheur->th_tfo_data_loss >= TFO_MAX_COOKIE_LOSS)
			__tcp_heuristic_tfo_middlebox_common(tpheur);
	}

	if ((flags & TCPCACHE_F_TFO_REQ) && tpheur->th_tfo_req_loss < TCP_CACHE_OVERFLOW_PROTECT) {
		tpheur->th_tfo_req_loss++;

		if (tpheur->th_tfo_req_loss >= TFO_MAX_COOKIE_LOSS)
			__tcp_heuristic_tfo_middlebox_common(tpheur);
	}

	if ((flags & TCPCACHE_F_TFO_DATA_RST) && tpheur->th_tfo_data_rst < TCP_CACHE_OVERFLOW_PROTECT) {
		tpheur->th_tfo_data_rst++;

		if (tpheur->th_tfo_data_rst >= TFO_MAX_COOKIE_LOSS)
			__tcp_heuristic_tfo_middlebox_common(tpheur);
	}

	if ((flags & TCPCACHE_F_TFO_REQ_RST) && tpheur->th_tfo_req_rst < TCP_CACHE_OVERFLOW_PROTECT) {
		tpheur->th_tfo_req_rst++;

		if (tpheur->th_tfo_req_rst >= TFO_MAX_COOKIE_LOSS)
			__tcp_heuristic_tfo_middlebox_common(tpheur);
	}

	if ((flags & TCPCACHE_F_ECN) && tpheur->th_ecn_loss < TCP_CACHE_OVERFLOW_PROTECT) {
		tpheur->th_ecn_loss++;
		if (tpheur->th_ecn_loss >= ECN_MAX_SYN_LOSS) {
			tcpstat.tcps_ecn_fallback_synloss++;
			TCP_CACHE_INC_IFNET_STAT(tcks->ifp, tcks->af, ecn_fallback_synloss);
			tpheur->th_ecn_backoff = tcp_now +
			    (tcp_min_to_hz(tcp_ecn_timeout) <<
			    (tpheur->th_ecn_loss - ECN_MAX_SYN_LOSS));
		}
	}

	if ((flags & TCPCACHE_F_MPTCP) &&
	    tpheur->th_mptcp_loss < TCP_CACHE_OVERFLOW_PROTECT) {
		tpheur->th_mptcp_loss++;
		if (tpheur->th_mptcp_loss >= MPTCP_MAX_SYN_LOSS) {
			/*
			 * Yes, we take tcp_ecn_timeout, to avoid adding yet
			 * another sysctl that is just used for testing.
			 */
			tpheur->th_mptcp_backoff = tcp_now +
			    (tcp_min_to_hz(tcp_ecn_timeout) <<
			    (tpheur->th_mptcp_loss - MPTCP_MAX_SYN_LOSS));
		}
	}

	if ((flags & TCPCACHE_F_ECN_DROPRST) &&
	    tpheur->th_ecn_droprst < TCP_CACHE_OVERFLOW_PROTECT) {
		tpheur->th_ecn_droprst++;
		if (tpheur->th_ecn_droprst >= ECN_MAX_DROPRST) {
			tcpstat.tcps_ecn_fallback_droprst++;
			TCP_CACHE_INC_IFNET_STAT(tcks->ifp, tcks->af,
			    ecn_fallback_droprst);
			tpheur->th_ecn_backoff = tcp_now +
			    (tcp_min_to_hz(tcp_ecn_timeout) <<
			    (tpheur->th_ecn_droprst - ECN_MAX_DROPRST));

		}
	}

	if ((flags & TCPCACHE_F_ECN_DROPRXMT) &&
	    tpheur->th_ecn_droprxmt < TCP_CACHE_OVERFLOW_PROTECT) {
		tpheur->th_ecn_droprxmt++;
		if (tpheur->th_ecn_droprxmt >= ECN_MAX_DROPRXMT) {
			tcpstat.tcps_ecn_fallback_droprxmt++;
			TCP_CACHE_INC_IFNET_STAT(tcks->ifp, tcks->af,
			    ecn_fallback_droprxmt);
			tpheur->th_ecn_backoff = tcp_now +
			    (tcp_min_to_hz(tcp_ecn_timeout) <<
			    (tpheur->th_ecn_droprxmt - ECN_MAX_DROPRXMT));
		}
	}
	if ((flags & TCPCACHE_F_ECN_SYNRST) &&
	    tpheur->th_ecn_synrst < TCP_CACHE_OVERFLOW_PROTECT) {
		tpheur->th_ecn_synrst++;
		if (tpheur->th_ecn_synrst >= ECN_MAX_SYNRST) {
			tcpstat.tcps_ecn_fallback_synrst++;
			TCP_CACHE_INC_IFNET_STAT(tcks->ifp, tcks->af,
			    ecn_fallback_synrst);
			tpheur->th_ecn_backoff = tcp_now +
			    (tcp_min_to_hz(tcp_ecn_timeout) <<
			    (tpheur->th_ecn_synrst - ECN_MAX_SYNRST));
		}
	}
	tcp_heuristic_unlock(head);
}