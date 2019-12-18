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
typedef  int /*<<< orphan*/  u_int16_t ;
struct ifnet {int /*<<< orphan*/  if_llreach_lock; int /*<<< orphan*/  if_ll_srcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  proto; } ;
struct if_llreach {int /*<<< orphan*/  lr_lastrcvd; TYPE_1__ lr_key; } ;

/* Variables and functions */
 unsigned int IF_LLREACH_MAXLEN ; 
 struct if_llreach* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct if_llreach*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bcopy (void*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll_reach_tree ; 
 int /*<<< orphan*/  net_uptime () ; 

void
ifnet_llreach_set_reachable(struct ifnet *ifp, u_int16_t llproto, void *addr,
    unsigned int alen)
{
	struct if_llreach find, *lr;

	VERIFY(alen == IF_LLREACH_MAXLEN);	/* for now */

	find.lr_key.proto = llproto;
	bcopy(addr, &find.lr_key.addr, IF_LLREACH_MAXLEN);

	lck_rw_lock_shared(&ifp->if_llreach_lock);
	lr = RB_FIND(ll_reach_tree, &ifp->if_ll_srcs, &find);
	if (lr == NULL) {
		lck_rw_done(&ifp->if_llreach_lock);
		return;
	}
	/*
	 * No need for lr_lock; atomically update the last rcvd uptime.
	 */
	lr->lr_lastrcvd = net_uptime();
	lck_rw_done(&ifp->if_llreach_lock);
}