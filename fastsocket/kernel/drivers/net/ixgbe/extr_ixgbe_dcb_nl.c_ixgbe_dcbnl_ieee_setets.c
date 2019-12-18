#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int mtu; } ;
struct TYPE_5__ {scalar_t__ pg_tcs; } ;
struct TYPE_6__ {TYPE_1__ num_tcs; } ;
struct ixgbe_adapter {int dcbx_cap; int /*<<< orphan*/  hw; TYPE_2__ dcb_cfg; TYPE_3__* ixgbe_ieee_ets; } ;
struct ieee_ets {scalar_t__* prio_tc; } ;
typedef  scalar_t__ __u8 ;
struct TYPE_7__ {int* prio_tc; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_VER_IEEE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE_8021QAZ_MAX_TCS ; 
 int ixgbe_dcb_hw_ets (int /*<<< orphan*/ *,struct ieee_ets*,int) ; 
 int /*<<< orphan*/  ixgbe_dcb_read_rtrup2tc (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ixgbe_dcbnl_devreset (struct net_device*) ; 
 int ixgbe_setup_tc (struct net_device*,scalar_t__) ; 
 TYPE_3__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct ieee_ets*,int) ; 
 scalar_t__ netdev_get_num_tc (struct net_device*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_dcbnl_ieee_setets(struct net_device *dev,
				   struct ieee_ets *ets)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	int max_frame = dev->mtu + ETH_HLEN + ETH_FCS_LEN;
	int i, err = 0;
	__u8 max_tc = 0;
	__u8 map_chg = 0;

	if (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		return -EINVAL;

	if (!adapter->ixgbe_ieee_ets) {
		adapter->ixgbe_ieee_ets = kmalloc(sizeof(struct ieee_ets),
						  GFP_KERNEL);
		if (!adapter->ixgbe_ieee_ets)
			return -ENOMEM;

		/* initialize UP2TC mappings to invalid value */
		for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			adapter->ixgbe_ieee_ets->prio_tc[i] =
				IEEE_8021QAZ_MAX_TCS;
		/* if possible update UP2TC mappings from HW */
		ixgbe_dcb_read_rtrup2tc(&adapter->hw,
					adapter->ixgbe_ieee_ets->prio_tc);
	}

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->prio_tc[i] > max_tc)
			max_tc = ets->prio_tc[i];
		if (ets->prio_tc[i] != adapter->ixgbe_ieee_ets->prio_tc[i])
			map_chg = 1;
	}

	memcpy(adapter->ixgbe_ieee_ets, ets, sizeof(*adapter->ixgbe_ieee_ets));

	if (max_tc)
		max_tc++;

	if (max_tc > adapter->dcb_cfg.num_tcs.pg_tcs)
		return -EINVAL;

	if (max_tc != netdev_get_num_tc(dev))
		err = ixgbe_setup_tc(dev, max_tc);
	else if (map_chg)
		ixgbe_dcbnl_devreset(dev);

	if (err)
		goto err_out;

	err = ixgbe_dcb_hw_ets(&adapter->hw, ets, max_frame);
err_out:
	return err;
}