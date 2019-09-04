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
struct rt_reach_info {int /*<<< orphan*/  ri_npm; int /*<<< orphan*/  ri_lqm; int /*<<< orphan*/  ri_rssi; int /*<<< orphan*/  ri_rcv_expire; int /*<<< orphan*/  ri_probes; int /*<<< orphan*/  ri_refcnt; } ;
struct if_llreach_info {int /*<<< orphan*/  lri_npm; int /*<<< orphan*/  lri_lqm; int /*<<< orphan*/  lri_rssi; int /*<<< orphan*/  lri_expire; int /*<<< orphan*/  lri_probes; int /*<<< orphan*/  lri_refcnt; } ;
struct if_llreach {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLR_LOCK_ASSERT_HELD (struct if_llreach*) ; 
 int /*<<< orphan*/  bzero (struct rt_reach_info*,int) ; 
 int /*<<< orphan*/  ifnet_lr2lri (struct if_llreach*,struct if_llreach_info*) ; 

void
ifnet_lr2ri(struct if_llreach *lr, struct rt_reach_info *ri)
{
	struct if_llreach_info lri;

	IFLR_LOCK_ASSERT_HELD(lr);

	bzero(ri, sizeof (*ri));
	ifnet_lr2lri(lr, &lri);
	ri->ri_refcnt = lri.lri_refcnt;
	ri->ri_probes = lri.lri_probes;
	ri->ri_rcv_expire = lri.lri_expire;
	ri->ri_rssi = lri.lri_rssi;
	ri->ri_lqm = lri.lri_lqm;
	ri->ri_npm = lri.lri_npm;
}