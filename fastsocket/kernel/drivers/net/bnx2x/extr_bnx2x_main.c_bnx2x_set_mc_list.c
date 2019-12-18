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
struct bnx2x_mcast_ramrod_params {int /*<<< orphan*/ * mcast_obj; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {int /*<<< orphan*/  mcast_obj; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int /*<<< orphan*/  BNX2X_MCAST_CMD_ADD ; 
 int /*<<< orphan*/  BNX2X_MCAST_CMD_DEL ; 
 int bnx2x_config_mcast (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_free_mcast_macs_list (struct bnx2x_mcast_ramrod_params*) ; 
 int bnx2x_init_mcast_macs_list (struct bnx2x*,struct bnx2x_mcast_ramrod_params*) ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 

__attribute__((used)) static int bnx2x_set_mc_list(struct bnx2x *bp)
{
	struct net_device *dev = bp->dev;
	struct bnx2x_mcast_ramrod_params rparam = {NULL};
	int rc = 0;

	rparam.mcast_obj = &bp->mcast_obj;

	/* first, clear all configured multicast MACs */
	rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_DEL);
	if (rc < 0) {
		BNX2X_ERR("Failed to clear multicast configuration: %d\n", rc);
		return rc;
	}

	/* then, configure a new MACs list */
	if (netdev_mc_count(dev)) {
		rc = bnx2x_init_mcast_macs_list(bp, &rparam);
		if (rc) {
			BNX2X_ERR("Failed to create multicast MACs list: %d\n",
				  rc);
			return rc;
		}

		/* Now add the new MACs */
		rc = bnx2x_config_mcast(bp, &rparam,
					BNX2X_MCAST_CMD_ADD);
		if (rc < 0)
			BNX2X_ERR("Failed to set a new multicast configuration: %d\n",
				  rc);

		bnx2x_free_mcast_macs_list(&rparam);
	}

	return rc;
}