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
struct TYPE_10__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_7__ {scalar_t__ sa_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
union sockaddr_in_4_6 {TYPE_5__ sin; TYPE_2__ sa; TYPE_1__ sin6; } ;
typedef  int /*<<< orphan*/  tcks ;
struct TYPE_9__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
struct tcp_cache_key_src {scalar_t__ af; TYPE_4__ faddr; TYPE_3__ laddr; struct ifnet* ifp; } ;
struct necp_tcp_tfo_cache {int /*<<< orphan*/  necp_tcp_tfo_cookie_len; int /*<<< orphan*/  necp_tcp_tfo_cookie; scalar_t__ necp_tcp_tfo_heuristics_middlebox; scalar_t__ necp_tcp_tfo_heuristics_rst_req; scalar_t__ necp_tcp_tfo_heuristics_rst_data; scalar_t__ necp_tcp_tfo_heuristics_loss_req; scalar_t__ necp_tcp_tfo_heuristics_loss; scalar_t__ necp_tcp_tfo_heuristics_success_req; scalar_t__ necp_tcp_tfo_heuristics_success; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int TCPCACHE_F_TFO_DATA ; 
 int TCPCACHE_F_TFO_DATA_RST ; 
 int TCPCACHE_F_TFO_REQ ; 
 int TCPCACHE_F_TFO_REQ_RST ; 
 int /*<<< orphan*/  calculate_tcp_clock () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct tcp_cache_key_src*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_cache_set_cookie_common (struct tcp_cache_key_src*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_heuristic_inc_counters (struct tcp_cache_key_src*,int) ; 
 int /*<<< orphan*/  tcp_heuristic_reset_counters (struct tcp_cache_key_src*,int) ; 
 int /*<<< orphan*/  tcp_heuristic_tfo_middlebox_common (struct tcp_cache_key_src*) ; 

void tcp_heuristics_tfo_update(struct necp_tcp_tfo_cache *necp_buffer,
    struct ifnet *ifp, union sockaddr_in_4_6 *local_address,
    union sockaddr_in_4_6 *remote_address)
{
	struct tcp_cache_key_src tcks;

	memset(&tcks, 0, sizeof(tcks));
	tcks.ifp = ifp;

	calculate_tcp_clock();

	if (remote_address->sa.sa_family == AF_INET6) {
		memcpy(&tcks.laddr.addr6, &local_address->sin6.sin6_addr, sizeof(struct in6_addr));
		memcpy(&tcks.faddr.addr6, &remote_address->sin6.sin6_addr, sizeof(struct in6_addr));
		tcks.af = AF_INET6;
	} else if (remote_address->sa.sa_family == AF_INET) {
		memcpy(&tcks.laddr.addr, &local_address->sin.sin_addr, sizeof(struct in_addr));
		memcpy(&tcks.faddr.addr, &remote_address->sin.sin_addr, sizeof(struct in_addr));
		tcks.af = AF_INET;
	}

	if (necp_buffer->necp_tcp_tfo_heuristics_success)
		tcp_heuristic_reset_counters(&tcks, TCPCACHE_F_TFO_REQ | TCPCACHE_F_TFO_DATA |
						    TCPCACHE_F_TFO_REQ_RST | TCPCACHE_F_TFO_DATA_RST);

	if (necp_buffer->necp_tcp_tfo_heuristics_success_req)
		tcp_heuristic_reset_counters(&tcks, TCPCACHE_F_TFO_REQ | TCPCACHE_F_TFO_REQ_RST);

	if (necp_buffer->necp_tcp_tfo_heuristics_loss)
		tcp_heuristic_inc_counters(&tcks, TCPCACHE_F_TFO_REQ | TCPCACHE_F_TFO_DATA);

	if (necp_buffer->necp_tcp_tfo_heuristics_loss_req)
		tcp_heuristic_inc_counters(&tcks, TCPCACHE_F_TFO_REQ);

	if (necp_buffer->necp_tcp_tfo_heuristics_rst_data)
		tcp_heuristic_inc_counters(&tcks, TCPCACHE_F_TFO_REQ_RST | TCPCACHE_F_TFO_DATA_RST);

	if (necp_buffer->necp_tcp_tfo_heuristics_rst_req)
		tcp_heuristic_inc_counters(&tcks, TCPCACHE_F_TFO_REQ_RST);

	if (necp_buffer->necp_tcp_tfo_heuristics_middlebox)
		tcp_heuristic_tfo_middlebox_common(&tcks);

	if (necp_buffer->necp_tcp_tfo_cookie_len != 0) {
		tcp_cache_set_cookie_common(&tcks,
			necp_buffer->necp_tcp_tfo_cookie, necp_buffer->necp_tcp_tfo_cookie_len);
	}

	return;
}