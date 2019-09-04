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
typedef  int uint32_t ;
struct tcpcb {int t_tfo_stats; } ;
struct tcp_cache_key_src {int dummy; } ;

/* Variables and functions */
 int TCPCACHE_F_TFO_DATA_RST ; 
 int TCPCACHE_F_TFO_REQ_RST ; 
 int TFO_S_COOKIE_REQ ; 
 int TFO_S_SYN_DATA_SENT ; 
 int /*<<< orphan*/  tcp_cache_key_src_create (struct tcpcb*,struct tcp_cache_key_src*) ; 
 int /*<<< orphan*/  tcp_heuristic_inc_counters (struct tcp_cache_key_src*,int) ; 

void tcp_heuristic_tfo_rst(struct tcpcb *tp)
{
	struct tcp_cache_key_src tcks;
	uint32_t flag = 0;

	tcp_cache_key_src_create(tp, &tcks);

	if (tp->t_tfo_stats & TFO_S_SYN_DATA_SENT)
		flag = (TCPCACHE_F_TFO_DATA_RST | TCPCACHE_F_TFO_REQ_RST);
	if (tp->t_tfo_stats & TFO_S_COOKIE_REQ)
		flag = TCPCACHE_F_TFO_REQ_RST;

	tcp_heuristic_inc_counters(&tcks, flag);
}