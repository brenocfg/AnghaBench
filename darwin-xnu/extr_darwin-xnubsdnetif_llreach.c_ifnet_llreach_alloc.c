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
typedef  scalar_t__ u_int64_t ;
typedef  void* u_int16_t ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct ifnet {int /*<<< orphan*/  if_llreach_lock; int /*<<< orphan*/  if_ll_srcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; void* proto; } ;
struct if_llreach {int lr_reqcnt; int lr_basereachable; int /*<<< orphan*/  lr_npm; int /*<<< orphan*/  lr_lqm; int /*<<< orphan*/  lr_rssi; TYPE_1__ lr_key; struct ifnet* lr_ifp; int /*<<< orphan*/  lr_debug; int /*<<< orphan*/  lr_reachable; int /*<<< orphan*/  lr_basecal; void* lr_lastrcvd; void* lr_baseup; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFD_ATTACHED ; 
 int /*<<< orphan*/  IFLR_ADDREF_LOCKED (struct if_llreach*) ; 
 int /*<<< orphan*/  IFLR_LOCK (struct if_llreach*) ; 
 int /*<<< orphan*/  IFLR_UNLOCK (struct if_llreach*) ; 
 int /*<<< orphan*/  IFNET_LQM_THRESH_UNKNOWN ; 
 int /*<<< orphan*/  IFNET_NPM_THRESH_UNKNOWN ; 
 int /*<<< orphan*/  IFNET_RSSI_UNKNOWN ; 
 unsigned int IF_LLREACH_MAXLEN ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LL_COMPUTE_RTIME (int) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct if_llreach* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct if_llreach*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct if_llreach*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bcopy (void*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 struct if_llreach* iflr_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared_to_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll_reach_tree ; 
 void* net_uptime () ; 

struct if_llreach *
ifnet_llreach_alloc(struct ifnet *ifp, u_int16_t llproto, void *addr,
    unsigned int alen, u_int64_t llreach_base)
{
	struct if_llreach find, *lr;
	struct timeval cnow;

	if (llreach_base == 0)
		return (NULL);

	VERIFY(alen == IF_LLREACH_MAXLEN);	/* for now */

	find.lr_key.proto = llproto;
	bcopy(addr, &find.lr_key.addr, IF_LLREACH_MAXLEN);

	lck_rw_lock_shared(&ifp->if_llreach_lock);
	lr = RB_FIND(ll_reach_tree, &ifp->if_ll_srcs, &find);
	if (lr != NULL) {
found:
		IFLR_LOCK(lr);
		VERIFY(lr->lr_reqcnt >= 1);
		lr->lr_reqcnt++;
		VERIFY(lr->lr_reqcnt != 0);
		IFLR_ADDREF_LOCKED(lr);		/* for caller */
		lr->lr_lastrcvd = net_uptime();	/* current approx. uptime */
		IFLR_UNLOCK(lr);
		lck_rw_done(&ifp->if_llreach_lock);
		return (lr);
	}

	if (!lck_rw_lock_shared_to_exclusive(&ifp->if_llreach_lock))
		lck_rw_lock_exclusive(&ifp->if_llreach_lock);

	LCK_RW_ASSERT(&ifp->if_llreach_lock, LCK_RW_ASSERT_EXCLUSIVE);

	/* in case things have changed while becoming writer */
	lr = RB_FIND(ll_reach_tree, &ifp->if_ll_srcs, &find);
	if (lr != NULL)
		goto found;

	lr = iflr_alloc(M_WAITOK);
	if (lr == NULL) {
		lck_rw_done(&ifp->if_llreach_lock);
		return (NULL);
	}
	IFLR_LOCK(lr);
	lr->lr_reqcnt++;
	VERIFY(lr->lr_reqcnt == 1);
	IFLR_ADDREF_LOCKED(lr);			/* for RB tree */
	IFLR_ADDREF_LOCKED(lr);			/* for caller */
	lr->lr_lastrcvd = net_uptime();		/* current approx. uptime */
	lr->lr_baseup = lr->lr_lastrcvd;	/* base uptime */
	getmicrotime(&cnow);
	lr->lr_basecal = cnow.tv_sec;		/* base calendar time */
	lr->lr_basereachable = llreach_base;
	lr->lr_reachable = LL_COMPUTE_RTIME(lr->lr_basereachable * 1000);
	lr->lr_debug |= IFD_ATTACHED;
	lr->lr_ifp = ifp;
	lr->lr_key.proto = llproto;
	bcopy(addr, &lr->lr_key.addr, IF_LLREACH_MAXLEN);
	lr->lr_rssi = IFNET_RSSI_UNKNOWN;
	lr->lr_lqm = IFNET_LQM_THRESH_UNKNOWN;
	lr->lr_npm = IFNET_NPM_THRESH_UNKNOWN;
	RB_INSERT(ll_reach_tree, &ifp->if_ll_srcs, lr);
	IFLR_UNLOCK(lr);
	lck_rw_done(&ifp->if_llreach_lock);

	return (lr);
}