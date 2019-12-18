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
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ERANGE ; 
 int ETH_P_1588 ; 
#define  HWTSTAMP_FILTER_ALL 143 
#define  HWTSTAMP_FILTER_NONE 142 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 141 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 140 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 139 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 138 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 137 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 136 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 135 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 134 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 133 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 132 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 131 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 130 
#define  HWTSTAMP_TX_OFF 129 
#define  HWTSTAMP_TX_ON 128 
 int /*<<< orphan*/  IXGBE_ETQF (int /*<<< orphan*/ ) ; 
 int IXGBE_ETQF_1588 ; 
 int /*<<< orphan*/  IXGBE_ETQF_FILTER_1588 ; 
 int IXGBE_ETQF_FILTER_EN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXMTRL ; 
 int IXGBE_RXMTRL_V1_DELAY_REQ_MSG ; 
 int IXGBE_RXMTRL_V1_SYNC_MSG ; 
 int /*<<< orphan*/  IXGBE_RXSTMPH ; 
 int /*<<< orphan*/  IXGBE_TSYNCRXCTL ; 
 int IXGBE_TSYNCRXCTL_ENABLED ; 
 int IXGBE_TSYNCRXCTL_TYPE_EVENT_V2 ; 
 int IXGBE_TSYNCRXCTL_TYPE_L4_V1 ; 
 int IXGBE_TSYNCRXCTL_TYPE_MASK ; 
 int /*<<< orphan*/  IXGBE_TSYNCTXCTL ; 
 int IXGBE_TSYNCTXCTL_ENABLED ; 
 int /*<<< orphan*/  IXGBE_TXSTMPH ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int PTP_EV_PORT ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 scalar_t__ ixgbe_mac_82598EB ; 

int ixgbe_ptp_hwtstamp_ioctl(struct ixgbe_adapter *adapter,
			     struct ifreq *ifr, int cmd)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct hwtstamp_config config;
	u32 tsync_tx_ctl = IXGBE_TSYNCTXCTL_ENABLED;
	u32 tsync_rx_ctl = IXGBE_TSYNCRXCTL_ENABLED;
	u32 tsync_rx_mtrl = PTP_EV_PORT << 16;
	bool is_l2 = false;
	u32 regval;

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	/* reserved for future extensions */
	if (config.flags)
		return -EINVAL;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		tsync_tx_ctl = 0;
	case HWTSTAMP_TX_ON:
		break;
	default:
		return -ERANGE;
	}

	switch (config.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		tsync_rx_ctl = 0;
		tsync_rx_mtrl = 0;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_mtrl |= IXGBE_RXMTRL_V1_SYNC_MSG;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_mtrl |= IXGBE_RXMTRL_V1_DELAY_REQ_MSG;
		break;
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		tsync_rx_ctl |= IXGBE_TSYNCRXCTL_TYPE_EVENT_V2;
		is_l2 = true;
		config.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_ALL:
	default:
		/*
		 * register RXMTRL must be set in order to do V1 packets,
		 * therefore it is not possible to time stamp both V1 Sync and
		 * Delay_Req messages and hardware does not support
		 * timestamping all packets => return error
		 */
		config.rx_filter = HWTSTAMP_FILTER_NONE;
		return -ERANGE;
	}

	if (hw->mac.type == ixgbe_mac_82598EB) {
		if (tsync_rx_ctl | tsync_tx_ctl)
			return -ERANGE;
		return 0;
	}

	/* define ethertype filter for timestamping L2 packets */
	if (is_l2)
		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_1588),
				(IXGBE_ETQF_FILTER_EN | /* enable filter */
				 IXGBE_ETQF_1588 | /* enable timestamping */
				 ETH_P_1588));     /* 1588 eth protocol type */
	else
		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_1588), 0);


	/* enable/disable TX */
	regval = IXGBE_READ_REG(hw, IXGBE_TSYNCTXCTL);
	regval &= ~IXGBE_TSYNCTXCTL_ENABLED;
	regval |= tsync_tx_ctl;
	IXGBE_WRITE_REG(hw, IXGBE_TSYNCTXCTL, regval);

	/* enable/disable RX */
	regval = IXGBE_READ_REG(hw, IXGBE_TSYNCRXCTL);
	regval &= ~(IXGBE_TSYNCRXCTL_ENABLED | IXGBE_TSYNCRXCTL_TYPE_MASK);
	regval |= tsync_rx_ctl;
	IXGBE_WRITE_REG(hw, IXGBE_TSYNCRXCTL, regval);

	/* define which PTP packets are time stamped */
	IXGBE_WRITE_REG(hw, IXGBE_RXMTRL, tsync_rx_mtrl);

	IXGBE_WRITE_FLUSH(hw);

	/* clear TX/RX time stamp registers, just to be sure */
	regval = IXGBE_READ_REG(hw, IXGBE_TXSTMPH);
	regval = IXGBE_READ_REG(hw, IXGBE_RXSTMPH);

	return copy_to_user(ifr->ifr_data, &config, sizeof(config)) ?
		-EFAULT : 0;
}