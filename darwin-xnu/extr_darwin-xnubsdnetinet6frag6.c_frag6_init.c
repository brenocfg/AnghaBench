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
struct ip6q {int dummy; } ;
struct ip6asfrag {int dummy; } ;
struct TYPE_2__ {struct TYPE_2__* ip6q_prev; struct TYPE_2__* ip6q_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CASSERT (int) ; 
 int _MLEN ; 
 int ip6_maxfragpackets ; 
 int ip6_maxfrags ; 
 TYPE_1__ ip6q ; 
 int /*<<< orphan*/  ip6q_updateparams () ; 
 int /*<<< orphan*/  ip6qlock ; 
 int /*<<< orphan*/  ip6qlock_attr ; 
 int /*<<< orphan*/  ip6qlock_grp ; 
 int /*<<< orphan*/  ip6qlock_grp_attr ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int nmbclusters ; 

void
frag6_init(void)
{
	/* ip6q_alloc() uses mbufs for IPv6 fragment queue structures */
	_CASSERT(sizeof (struct ip6q) <= _MLEN);
	/* ip6af_alloc() uses mbufs for IPv6 fragment queue structures */
	_CASSERT(sizeof (struct ip6asfrag) <= _MLEN);

	/* IPv6 fragment reassembly queue lock */
	ip6qlock_grp_attr  = lck_grp_attr_alloc_init();
	ip6qlock_grp = lck_grp_alloc_init("ip6qlock", ip6qlock_grp_attr);
	ip6qlock_attr = lck_attr_alloc_init();
	lck_mtx_init(&ip6qlock, ip6qlock_grp, ip6qlock_attr);

	lck_mtx_lock(&ip6qlock);
	/* Initialize IPv6 reassembly queue. */
	ip6q.ip6q_next = ip6q.ip6q_prev = &ip6q;

	/* same limits as IPv4 */
	ip6_maxfragpackets = nmbclusters / 32;
	ip6_maxfrags = ip6_maxfragpackets * 2;
	ip6q_updateparams();
	lck_mtx_unlock(&ip6qlock);
}