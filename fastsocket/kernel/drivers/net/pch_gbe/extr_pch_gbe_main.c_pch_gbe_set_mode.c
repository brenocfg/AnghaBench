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
typedef  int u16 ;
struct pch_gbe_hw {TYPE_1__* reg; } ;
struct pch_gbe_adapter {struct pch_gbe_hw hw; struct net_device* netdev; } ;
struct net_device {int tx_queue_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  MODE; } ;

/* Variables and functions */
 int DUPLEX_FULL ; 
 unsigned long PCH_GBE_MODE_FULL_DUPLEX ; 
 unsigned long PCH_GBE_MODE_GMII_ETHER ; 
 unsigned long PCH_GBE_MODE_HALF_DUPLEX ; 
 unsigned long PCH_GBE_MODE_MII_ETHER ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  iowrite32 (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_gbe_set_mode(struct pch_gbe_adapter *adapter, u16 speed,
			      u16 duplex)
{
	struct net_device *netdev = adapter->netdev;
	struct pch_gbe_hw *hw = &adapter->hw;
	unsigned long mode = 0;

	/* Set the communication mode */
	switch (speed) {
	case SPEED_10:
		mode = PCH_GBE_MODE_MII_ETHER;
		netdev->tx_queue_len = 10;
		break;
	case SPEED_100:
		mode = PCH_GBE_MODE_MII_ETHER;
		netdev->tx_queue_len = 100;
		break;
	case SPEED_1000:
		mode = PCH_GBE_MODE_GMII_ETHER;
		break;
	}
	if (duplex == DUPLEX_FULL)
		mode |= PCH_GBE_MODE_FULL_DUPLEX;
	else
		mode |= PCH_GBE_MODE_HALF_DUPLEX;
	iowrite32(mode, &hw->reg->MODE);
}