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
typedef  int u32 ;
struct antenna_setup {int tx; int rx; } ;
struct link_ant {int flags; } ;
struct TYPE_2__ {struct link_ant ant; } ;
struct rt2x00_dev {struct antenna_setup default_ant; TYPE_1__ link; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;

/* Variables and functions */
 int ANTENNA_RX_DIVERSITY ; 
 int ANTENNA_SW_DIVERSITY ; 
 int ANTENNA_TX_DIVERSITY ; 
 int EINVAL ; 
 int /*<<< orphan*/  rt2x00lib_config_antenna (struct rt2x00_dev*,struct antenna_setup) ; 

int rt2x00mac_set_antenna(struct ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	struct link_ant *ant = &rt2x00dev->link.ant;
	struct antenna_setup *def = &rt2x00dev->default_ant;
	struct antenna_setup setup;

	// The antenna value is not supposed to be 0,
	// or exceed the maximum number of antenna's.
	if (!tx_ant || (tx_ant & ~3) || !rx_ant || (rx_ant & ~3))
		return -EINVAL;

	// When the client tried to configure the antenna to or from
	// diversity mode, we must reset the default antenna as well
	// as that controls the diversity switch.
	if (ant->flags & ANTENNA_TX_DIVERSITY && tx_ant != 3)
		ant->flags &= ~ANTENNA_TX_DIVERSITY;
	if (ant->flags & ANTENNA_RX_DIVERSITY && rx_ant != 3)
		ant->flags &= ~ANTENNA_RX_DIVERSITY;

	// If diversity is being enabled, check if we need hardware
	// or software diversity. In the latter case, reset the value,
	// and make sure we update the antenna flags to have the
	// link tuner pick up the diversity tuning.
	if (tx_ant == 3 && def->tx == ANTENNA_SW_DIVERSITY) {
		tx_ant = ANTENNA_SW_DIVERSITY;
		ant->flags |= ANTENNA_TX_DIVERSITY;
	}

	if (rx_ant == 3 && def->rx == ANTENNA_SW_DIVERSITY) {
		rx_ant = ANTENNA_SW_DIVERSITY;
		ant->flags |= ANTENNA_RX_DIVERSITY;
	}

	setup.tx = tx_ant;
	setup.rx = rx_ant;

	rt2x00lib_config_antenna(rt2x00dev, setup);

	return 0;
}