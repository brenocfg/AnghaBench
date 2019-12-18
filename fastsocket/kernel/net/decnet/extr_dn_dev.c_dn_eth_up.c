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
struct net_device {struct dn_dev* dn_ptr; } ;
struct TYPE_2__ {scalar_t__ forwarding; } ;
struct dn_dev {int use_long; TYPE_1__ parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dev_mc_add (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_rt_all_end_mcast ; 
 int /*<<< orphan*/  dn_rt_all_rt_mcast ; 

__attribute__((used)) static int dn_eth_up(struct net_device *dev)
{
	struct dn_dev *dn_db = dev->dn_ptr;

	if (dn_db->parms.forwarding == 0)
		dev_mc_add(dev, dn_rt_all_end_mcast, ETH_ALEN, 0);
	else
		dev_mc_add(dev, dn_rt_all_rt_mcast, ETH_ALEN, 0);

	dn_db->use_long = 1;

	return 0;
}