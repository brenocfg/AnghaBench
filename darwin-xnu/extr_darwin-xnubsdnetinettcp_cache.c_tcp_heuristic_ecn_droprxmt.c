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
struct tcpcb {int dummy; } ;
struct tcp_cache_key_src {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPCACHE_F_ECN_DROPRXMT ; 
 int /*<<< orphan*/  tcp_cache_key_src_create (struct tcpcb*,struct tcp_cache_key_src*) ; 
 int /*<<< orphan*/  tcp_heuristic_inc_counters (struct tcp_cache_key_src*,int /*<<< orphan*/ ) ; 

void tcp_heuristic_ecn_droprxmt(struct tcpcb *tp)
{
	struct tcp_cache_key_src tcks;

	tcp_cache_key_src_create(tp, &tcks);

	tcp_heuristic_inc_counters(&tcks, TCPCACHE_F_ECN_DROPRXMT);
}