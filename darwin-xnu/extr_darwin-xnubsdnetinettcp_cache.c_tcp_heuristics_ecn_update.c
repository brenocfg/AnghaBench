#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_6__ {scalar_t__ sa_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
union sockaddr_in_4_6 {TYPE_4__ sin; TYPE_2__ sa; TYPE_1__ sin6; } ;
typedef  int /*<<< orphan*/  tcks ;
struct TYPE_7__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
struct tcp_cache_key_src {scalar_t__ af; TYPE_3__ laddr; struct ifnet* ifp; } ;
struct necp_tcp_ecn_cache {scalar_t__ necp_tcp_ecn_heuristics_aggressive; scalar_t__ necp_tcp_ecn_heuristics_syn_rst; scalar_t__ necp_tcp_ecn_heuristics_drop_rxmt; scalar_t__ necp_tcp_ecn_heuristics_drop_rst; scalar_t__ necp_tcp_ecn_heuristics_loss; scalar_t__ necp_tcp_ecn_heuristics_success; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  TCPCACHE_F_ECN ; 
 int /*<<< orphan*/  TCPCACHE_F_ECN_DROPRST ; 
 int /*<<< orphan*/  TCPCACHE_F_ECN_DROPRXMT ; 
 int /*<<< orphan*/  TCPCACHE_F_ECN_SYNRST ; 
 int /*<<< orphan*/  calculate_tcp_clock () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct tcp_cache_key_src*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_heuristic_ecn_aggressive_common (struct tcp_cache_key_src*) ; 
 int /*<<< orphan*/  tcp_heuristic_inc_counters (struct tcp_cache_key_src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_heuristic_reset_counters (struct tcp_cache_key_src*,int /*<<< orphan*/ ) ; 

void tcp_heuristics_ecn_update(struct necp_tcp_ecn_cache *necp_buffer,
    struct ifnet *ifp, union sockaddr_in_4_6 *local_address)
{
	struct tcp_cache_key_src tcks;

	memset(&tcks, 0, sizeof(tcks));
	tcks.ifp = ifp;

	calculate_tcp_clock();

	if (local_address->sa.sa_family == AF_INET6) {
		memcpy(&tcks.laddr.addr6, &local_address->sin6.sin6_addr, sizeof(struct in6_addr));
		tcks.af = AF_INET6;
	} else if (local_address->sa.sa_family == AF_INET) {
		memcpy(&tcks.laddr.addr, &local_address->sin.sin_addr, sizeof(struct in_addr));
		tcks.af = AF_INET;
	}

	if (necp_buffer->necp_tcp_ecn_heuristics_success) {
		tcp_heuristic_reset_counters(&tcks, TCPCACHE_F_ECN);
	} else if (necp_buffer->necp_tcp_ecn_heuristics_loss) {
		tcp_heuristic_inc_counters(&tcks, TCPCACHE_F_ECN);
	} else if (necp_buffer->necp_tcp_ecn_heuristics_drop_rst) {
		tcp_heuristic_inc_counters(&tcks, TCPCACHE_F_ECN_DROPRST);
	} else if (necp_buffer->necp_tcp_ecn_heuristics_drop_rxmt) {
		tcp_heuristic_inc_counters(&tcks, TCPCACHE_F_ECN_DROPRXMT);
	} else if (necp_buffer->necp_tcp_ecn_heuristics_syn_rst) {
		tcp_heuristic_inc_counters(&tcks, TCPCACHE_F_ECN_SYNRST);
	} else if (necp_buffer->necp_tcp_ecn_heuristics_aggressive) {
		tcp_heuristic_ecn_aggressive_common(&tcks);
	}

	return;
}