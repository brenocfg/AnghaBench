#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int8_t ;
struct tcp_heuristics_head {int dummy; } ;
struct tcp_heuristic {scalar_t__ th_mptcp_loss; scalar_t__ th_ecn_synrst; scalar_t__ th_ecn_loss; scalar_t__ th_tfo_req_rst; scalar_t__ th_tfo_data_rst; scalar_t__ th_tfo_req_loss; scalar_t__ th_tfo_data_loss; } ;
struct tcp_cache_key_src {int dummy; } ;

/* Variables and functions */
 int TCPCACHE_F_ECN ; 
 int TCPCACHE_F_MPTCP ; 
 int TCPCACHE_F_TFO_DATA ; 
 int TCPCACHE_F_TFO_DATA_RST ; 
 int TCPCACHE_F_TFO_REQ ; 
 int TCPCACHE_F_TFO_REQ_RST ; 
 struct tcp_heuristic* tcp_getheuristic_with_lock (struct tcp_cache_key_src*,int /*<<< orphan*/ ,struct tcp_heuristics_head**) ; 
 int /*<<< orphan*/  tcp_heuristic_unlock (struct tcp_heuristics_head*) ; 

__attribute__((used)) static void tcp_heuristic_reset_counters(struct tcp_cache_key_src *tcks, u_int8_t flags)
{
	struct tcp_heuristics_head *head;
	struct tcp_heuristic *tpheur;

	/*
	 * Don't attempt to create it! Keep the heuristics clean if the
	 * server does not support TFO. This reduces the lookup-cost on
	 * our side.
	 */
	tpheur = tcp_getheuristic_with_lock(tcks, 0, &head);
	if (tpheur == NULL)
		return;

	if (flags & TCPCACHE_F_TFO_DATA) {
		tpheur->th_tfo_data_loss = 0;
	}

	if (flags & TCPCACHE_F_TFO_REQ) {
		tpheur->th_tfo_req_loss = 0;
	}

	if (flags & TCPCACHE_F_TFO_DATA_RST) {
		tpheur->th_tfo_data_rst = 0;
	}

	if (flags & TCPCACHE_F_TFO_REQ_RST) {
		tpheur->th_tfo_req_rst = 0;
	}

	if (flags & TCPCACHE_F_ECN) {
		tpheur->th_ecn_loss = 0;
		tpheur->th_ecn_synrst = 0;
	}

	if (flags & TCPCACHE_F_MPTCP)
		tpheur->th_mptcp_loss = 0;

	tcp_heuristic_unlock(head);
}