#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pxofftxc; int /*<<< orphan*/ * pxoffrxc; } ;
struct TYPE_4__ {int /*<<< orphan*/  pfc_tcs; } ;
struct TYPE_5__ {TYPE_1__ num_tcs; } ;
struct ixgbe_adapter {TYPE_3__ stats; TYPE_2__ dcb_cfg; struct ieee_pfc* ixgbe_ieee_pfc; } ;
struct ieee_pfc {int /*<<< orphan*/ * indications; int /*<<< orphan*/ * requests; int /*<<< orphan*/  delay; int /*<<< orphan*/  mbc; int /*<<< orphan*/  pfc_en; int /*<<< orphan*/  pfc_cap; } ;

/* Variables and functions */
 int MAX_TRAFFIC_CLASS ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_dcbnl_ieee_getpfc(struct net_device *dev,
				   struct ieee_pfc *pfc)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	struct ieee_pfc *my_pfc = adapter->ixgbe_ieee_pfc;
	int i;

	pfc->pfc_cap = adapter->dcb_cfg.num_tcs.pfc_tcs;

	/* No IEEE PFC settings available */
	if (!my_pfc)
		return 0;

	pfc->pfc_en = my_pfc->pfc_en;
	pfc->mbc = my_pfc->mbc;
	pfc->delay = my_pfc->delay;

	for (i = 0; i < MAX_TRAFFIC_CLASS; i++) {
		pfc->requests[i] = adapter->stats.pxoffrxc[i];
		pfc->indications[i] = adapter->stats.pxofftxc[i];
	}

	return 0;
}