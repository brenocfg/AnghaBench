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
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct ifmcaddr6 {int mca_flags; int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  mca_refcnt; int /*<<< orphan*/  mca_timer; TYPE_1__* idev; int /*<<< orphan*/  mca_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dead; struct net_device* dev; } ;

/* Variables and functions */
 int MAF_LOADED ; 
 int MAF_NOREPORT ; 
 int MAX_ADDR_LEN ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_mc_delete (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igmp6_leave_group (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  ip6_mc_clear_src (struct ifmcaddr6*) ; 
 scalar_t__ ndisc_mc_map (int /*<<< orphan*/ *,char*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igmp6_group_dropped(struct ifmcaddr6 *mc)
{
	struct net_device *dev = mc->idev->dev;
	char buf[MAX_ADDR_LEN];

	spin_lock_bh(&mc->mca_lock);
	if (mc->mca_flags&MAF_LOADED) {
		mc->mca_flags &= ~MAF_LOADED;
		if (ndisc_mc_map(&mc->mca_addr, buf, dev, 0) == 0)
			dev_mc_delete(dev, buf, dev->addr_len, 0);
	}

	if (mc->mca_flags & MAF_NOREPORT)
		goto done;
	spin_unlock_bh(&mc->mca_lock);

	if (!mc->idev->dead)
		igmp6_leave_group(mc);

	spin_lock_bh(&mc->mca_lock);
	if (del_timer(&mc->mca_timer))
		atomic_dec(&mc->mca_refcnt);
done:
	ip6_mc_clear_src(mc);
	spin_unlock_bh(&mc->mca_lock);
}