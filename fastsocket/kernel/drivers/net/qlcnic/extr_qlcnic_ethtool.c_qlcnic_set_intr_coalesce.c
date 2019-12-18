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
typedef  void* u32 ;
struct qlcnic_nic_intr_coalesce {void* rx_time_us; void* rx_packets; void* tx_time_us; void* tx_packets; void* flag; void* type; } ;
struct qlcnic_adapter {TYPE_1__* ahw; int /*<<< orphan*/  state; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; int rx_max_coalesced_frames; int tx_coalesce_usecs; int tx_max_coalesced_frames; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_low; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; } ;
struct TYPE_2__ {struct qlcnic_nic_intr_coalesce coal; } ;

/* Variables and functions */
 int EINVAL ; 
 void* QLCNIC_DEF_INTR_COALESCE_RX_PACKETS ; 
 void* QLCNIC_DEF_INTR_COALESCE_RX_TIME_US ; 
 void* QLCNIC_DEF_INTR_COALESCE_TX_PACKETS ; 
 void* QLCNIC_DEF_INTR_COALESCE_TX_TIME_US ; 
 void* QLCNIC_INTR_COAL_TYPE_RX ; 
 void* QLCNIC_INTR_COAL_TYPE_TX ; 
 void* QLCNIC_INTR_DEFAULT ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_config_intr_coalesce (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_set_intr_coalesce(struct net_device *netdev,
			struct ethtool_coalesce *ethcoal)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_nic_intr_coalesce *coal;
	u32 rx_coalesce_usecs, rx_max_frames;
	u32 tx_coalesce_usecs, tx_max_frames;

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		return -EINVAL;

	/*
	* Return Error if unsupported values or
	* unsupported parameters are set.
	*/
	if (ethcoal->rx_coalesce_usecs > 0xffff ||
		ethcoal->rx_max_coalesced_frames > 0xffff ||
		ethcoal->tx_coalesce_usecs > 0xffff ||
		ethcoal->tx_max_coalesced_frames > 0xffff ||
		ethcoal->rx_coalesce_usecs_irq ||
		ethcoal->rx_max_coalesced_frames_irq ||
		ethcoal->tx_coalesce_usecs_irq ||
		ethcoal->tx_max_coalesced_frames_irq ||
		ethcoal->stats_block_coalesce_usecs ||
		ethcoal->use_adaptive_rx_coalesce ||
		ethcoal->use_adaptive_tx_coalesce ||
		ethcoal->pkt_rate_low ||
		ethcoal->rx_coalesce_usecs_low ||
		ethcoal->rx_max_coalesced_frames_low ||
		ethcoal->tx_coalesce_usecs_low ||
		ethcoal->tx_max_coalesced_frames_low ||
		ethcoal->pkt_rate_high ||
		ethcoal->rx_coalesce_usecs_high ||
		ethcoal->rx_max_coalesced_frames_high ||
		ethcoal->tx_coalesce_usecs_high ||
		ethcoal->tx_max_coalesced_frames_high)
		return -EINVAL;

	coal = &adapter->ahw->coal;

	if (qlcnic_83xx_check(adapter)) {
		if (!ethcoal->tx_coalesce_usecs ||
		    !ethcoal->tx_max_coalesced_frames ||
		    !ethcoal->rx_coalesce_usecs ||
		    !ethcoal->rx_max_coalesced_frames) {
			coal->flag = QLCNIC_INTR_DEFAULT;
			coal->type = QLCNIC_INTR_COAL_TYPE_RX;
			coal->rx_time_us = QLCNIC_DEF_INTR_COALESCE_RX_TIME_US;
			coal->rx_packets = QLCNIC_DEF_INTR_COALESCE_RX_PACKETS;
			coal->tx_time_us = QLCNIC_DEF_INTR_COALESCE_TX_TIME_US;
			coal->tx_packets = QLCNIC_DEF_INTR_COALESCE_TX_PACKETS;
		} else {
			tx_coalesce_usecs = ethcoal->tx_coalesce_usecs;
			tx_max_frames = ethcoal->tx_max_coalesced_frames;
			rx_coalesce_usecs = ethcoal->rx_coalesce_usecs;
			rx_max_frames = ethcoal->rx_max_coalesced_frames;
			coal->flag = 0;

			if ((coal->rx_time_us == rx_coalesce_usecs) &&
			    (coal->rx_packets == rx_max_frames)) {
				coal->type = QLCNIC_INTR_COAL_TYPE_TX;
				coal->tx_time_us = tx_coalesce_usecs;
				coal->tx_packets = tx_max_frames;
			} else if ((coal->tx_time_us == tx_coalesce_usecs) &&
				   (coal->tx_packets == tx_max_frames)) {
				coal->type = QLCNIC_INTR_COAL_TYPE_RX;
				coal->rx_time_us = rx_coalesce_usecs;
				coal->rx_packets = rx_max_frames;
			} else {
				coal->type = QLCNIC_INTR_COAL_TYPE_RX;
				coal->rx_time_us = rx_coalesce_usecs;
				coal->rx_packets = rx_max_frames;
				coal->tx_time_us = tx_coalesce_usecs;
				coal->tx_packets = tx_max_frames;
			}
		}
	} else {
		if (!ethcoal->rx_coalesce_usecs ||
		    !ethcoal->rx_max_coalesced_frames) {
			coal->flag = QLCNIC_INTR_DEFAULT;
			coal->rx_time_us = QLCNIC_DEF_INTR_COALESCE_RX_TIME_US;
			coal->rx_packets = QLCNIC_DEF_INTR_COALESCE_RX_PACKETS;
		} else {
			coal->flag = 0;
			coal->rx_time_us = ethcoal->rx_coalesce_usecs;
			coal->rx_packets = ethcoal->rx_max_coalesced_frames;
		}
	}

	qlcnic_config_intr_coalesce(adapter);

	return 0;
}