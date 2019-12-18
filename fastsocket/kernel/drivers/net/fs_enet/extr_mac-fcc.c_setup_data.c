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
struct fs_enet_private {int /*<<< orphan*/  ev_err; int /*<<< orphan*/  ev_tx; int /*<<< orphan*/  ev_rx; int /*<<< orphan*/  ev_napi_rx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FCC_ERR_EVENT_MSK ; 
 int /*<<< orphan*/  FCC_NAPI_RX_EVENT_MSK ; 
 int /*<<< orphan*/  FCC_RX_EVENT ; 
 int /*<<< orphan*/  FCC_TX_EVENT ; 
 scalar_t__ do_pd_setup (struct fs_enet_private*) ; 
 struct fs_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int setup_data(struct net_device *dev)
{
	struct fs_enet_private *fep = netdev_priv(dev);

	if (do_pd_setup(fep) != 0)
		return -EINVAL;

	fep->ev_napi_rx = FCC_NAPI_RX_EVENT_MSK;
	fep->ev_rx = FCC_RX_EVENT;
	fep->ev_tx = FCC_TX_EVENT;
	fep->ev_err = FCC_ERR_EVENT_MSK;

	return 0;
}