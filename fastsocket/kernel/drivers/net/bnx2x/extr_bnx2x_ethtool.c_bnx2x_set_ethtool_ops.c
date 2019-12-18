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
struct net_device {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_ethtool_ops ; 
 int /*<<< orphan*/  bnx2x_ethtool_ops_ext ; 
 int /*<<< orphan*/  bnx2x_vf_ethtool_ops ; 
 int /*<<< orphan*/  bnx2x_vf_ethtool_ops_ext ; 
 int /*<<< orphan*/  set_ethtool_ops_ext (struct net_device*,int /*<<< orphan*/ *) ; 

void bnx2x_set_ethtool_ops(struct bnx2x *bp, struct net_device *netdev)
{
	if (IS_PF(bp)) {
		SET_ETHTOOL_OPS(netdev, &bnx2x_ethtool_ops);
		set_ethtool_ops_ext(netdev, &bnx2x_ethtool_ops_ext);
	} else { /* vf */
		SET_ETHTOOL_OPS(netdev, &bnx2x_vf_ethtool_ops);
		set_ethtool_ops_ext(netdev, &bnx2x_vf_ethtool_ops_ext);
	}
}