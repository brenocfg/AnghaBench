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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int dcbx_cap; int dcb_set_bitmap; } ;
struct ieee_pfc {int pfc_cap; int /*<<< orphan*/  member_0; } ;
struct ieee_ets {int ets_cap; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int BIT_APP_UPCHG ; 
 int BIT_PFC ; 
 int BIT_PG_RX ; 
 int BIT_PG_TX ; 
 int DCB_CAP_DCBX_HOST ; 
 int DCB_CAP_DCBX_LLD_MANAGED ; 
 int DCB_CAP_DCBX_VER_CEE ; 
 int DCB_CAP_DCBX_VER_IEEE ; 
 int /*<<< orphan*/  ixgbe_dcbnl_ieee_setets (struct net_device*,struct ieee_ets*) ; 
 int /*<<< orphan*/  ixgbe_dcbnl_ieee_setpfc (struct net_device*,struct ieee_pfc*) ; 
 int /*<<< orphan*/  ixgbe_dcbnl_set_all (struct net_device*) ; 
 int ixgbe_setup_tc (struct net_device*,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 ixgbe_dcbnl_setdcbx(struct net_device *dev, u8 mode)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	struct ieee_ets ets = {0};
	struct ieee_pfc pfc = {0};
	int err = 0;

	/* no support for LLD_MANAGED modes or CEE+IEEE */
	if ((mode & DCB_CAP_DCBX_LLD_MANAGED) ||
	    ((mode & DCB_CAP_DCBX_VER_IEEE) && (mode & DCB_CAP_DCBX_VER_CEE)) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		return 1;

	if (mode == adapter->dcbx_cap)
		return 0;

	adapter->dcbx_cap = mode;

	/* ETS and PFC defaults */
	ets.ets_cap = 8;
	pfc.pfc_cap = 8;

	if (mode & DCB_CAP_DCBX_VER_IEEE) {
		ixgbe_dcbnl_ieee_setets(dev, &ets);
		ixgbe_dcbnl_ieee_setpfc(dev, &pfc);
	} else if (mode & DCB_CAP_DCBX_VER_CEE) {
		u8 mask = BIT_PFC | BIT_PG_TX | BIT_PG_RX | BIT_APP_UPCHG;

		adapter->dcb_set_bitmap |= mask;
		ixgbe_dcbnl_set_all(dev);
	} else {
		/* Drop into single TC mode strict priority as this
		 * indicates CEE and IEEE versions are disabled
		 */
		ixgbe_dcbnl_ieee_setets(dev, &ets);
		ixgbe_dcbnl_ieee_setpfc(dev, &pfc);
		err = ixgbe_setup_tc(dev, 0);
	}

	return err ? 1 : 0;
}