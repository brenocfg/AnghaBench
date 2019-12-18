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
typedef  scalar_t__ tcp_seq ;
struct TYPE_4__ {scalar_t__ s_addr; } ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct lro_flow {unsigned short lr_fport; unsigned short lr_lport; scalar_t__ lr_seq; int /*<<< orphan*/ * lr_tcphdr; TYPE_2__ lr_laddr; TYPE_1__ lr_faddr; } ;
struct in_addr {scalar_t__ s_addr; } ;
typedef  scalar_t__ __uint32_t ;

/* Variables and functions */
 int LRO_HASH (scalar_t__,scalar_t__,unsigned short,unsigned short,scalar_t__) ; 
 scalar_t__ TCP_LRO_FLOW_MAP ; 
 int TCP_LRO_FLOW_UNINIT ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 struct lro_flow* lro_flow_list ; 
 int* lro_flow_map ; 
 int /*<<< orphan*/  tcp_lro_lock ; 

void
tcp_update_lro_seq(__uint32_t rcv_nxt, struct in_addr saddr, struct in_addr daddr,
		unsigned short sport, unsigned short dport)
{
	int hash, flow_id;
	struct lro_flow *lf;

	hash = LRO_HASH(daddr.s_addr, saddr.s_addr, dport, sport, 
		(TCP_LRO_FLOW_MAP - 1));
	lck_mtx_lock_spin(&tcp_lro_lock);
	flow_id = lro_flow_map[hash];
	if (flow_id == TCP_LRO_FLOW_UNINIT) {
		lck_mtx_unlock(&tcp_lro_lock);
		return;
	}
	lf = &lro_flow_list[flow_id];
	if ((lf->lr_faddr.s_addr == daddr.s_addr) &&
	    (lf->lr_laddr.s_addr == saddr.s_addr) &&
	    (lf->lr_fport == dport) &&
	    (lf->lr_lport == sport) &&
	    (lf->lr_tcphdr == NULL)) {
		lf->lr_seq = (tcp_seq)rcv_nxt;
	}
	lck_mtx_unlock(&tcp_lro_lock);
	return;
}