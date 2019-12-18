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
struct if_llreach_info {int /*<<< orphan*/  lri_npm; int /*<<< orphan*/  lri_lqm; int /*<<< orphan*/  lri_rssi; int /*<<< orphan*/  lri_addr; int /*<<< orphan*/  lri_proto; int /*<<< orphan*/  lri_expire; int /*<<< orphan*/  lri_probes; int /*<<< orphan*/  lri_ifindex; int /*<<< orphan*/  lri_refcnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  proto; } ;
struct if_llreach {int /*<<< orphan*/  lr_npm; int /*<<< orphan*/  lr_lqm; int /*<<< orphan*/  lr_rssi; TYPE_2__ lr_key; int /*<<< orphan*/  lr_lastrcvd; int /*<<< orphan*/  lr_probes; TYPE_1__* lr_ifp; int /*<<< orphan*/  lr_reqcnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLR_LOCK_ASSERT_HELD (struct if_llreach*) ; 
 int /*<<< orphan*/  IF_LLREACH_MAXLEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct if_llreach_info*,int) ; 
 int /*<<< orphan*/  ifnet_llreach_up2calexp (struct if_llreach*,int /*<<< orphan*/ ) ; 

void
ifnet_lr2lri(struct if_llreach *lr, struct if_llreach_info *lri)
{
	IFLR_LOCK_ASSERT_HELD(lr);

	bzero(lri, sizeof (*lri));
	/*
	 * Note here we return request count, not actual memory refcnt.
	 */
	lri->lri_refcnt	= lr->lr_reqcnt;
	lri->lri_ifindex = lr->lr_ifp->if_index;
	lri->lri_probes	= lr->lr_probes;
	lri->lri_expire = ifnet_llreach_up2calexp(lr, lr->lr_lastrcvd);
	lri->lri_proto = lr->lr_key.proto;
	bcopy(&lr->lr_key.addr, &lri->lri_addr, IF_LLREACH_MAXLEN);
	lri->lri_rssi = lr->lr_rssi;
	lri->lri_lqm = lr->lr_lqm;
	lri->lri_npm = lr->lr_npm;
}