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
struct TYPE_6__ {void* keys; } ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {int /*<<< orphan*/  tx_status_drop; int /*<<< orphan*/  rx_handlers_fragments; int /*<<< orphan*/  rx_expand_skb_head2; int /*<<< orphan*/  rx_expand_skb_head; int /*<<< orphan*/  tx_expand_skb_head_cloned; int /*<<< orphan*/  tx_expand_skb_head; int /*<<< orphan*/  rx_handlers_drop_short; int /*<<< orphan*/  rx_handlers_drop_defrag; int /*<<< orphan*/  rx_handlers_drop_nullfunc; int /*<<< orphan*/  rx_handlers_queued; int /*<<< orphan*/  rx_handlers_drop; int /*<<< orphan*/  tx_handlers_drop_unauth_port; int /*<<< orphan*/  tx_handlers_drop_not_assoc; int /*<<< orphan*/  tx_handlers_drop_wep; int /*<<< orphan*/  tx_handlers_drop_fragment; int /*<<< orphan*/  tx_handlers_drop_unencrypted; int /*<<< orphan*/  tx_handlers_queued; int /*<<< orphan*/  tx_handlers_drop; int /*<<< orphan*/  dot11TransmittedFrameCount; int /*<<< orphan*/  dot11MulticastReceivedFrameCount; int /*<<< orphan*/  dot11ReceivedFragmentCount; int /*<<< orphan*/  dot11FrameDuplicateCount; int /*<<< orphan*/  dot11MultipleRetryCount; int /*<<< orphan*/  dot11RetryCount; int /*<<< orphan*/  dot11FailedCount; int /*<<< orphan*/  dot11MulticastTransmittedFrameCount; int /*<<< orphan*/  dot11TransmittedFragmentCount; TYPE_3__ debugfs; TYPE_2__ hw; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {struct dentry* debugfsdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGFS_ADD_MODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEBUGFS_DEVSTATS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGFS_STATS_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  dot11ACKFailureCount ; 
 int /*<<< orphan*/  dot11FCSErrorCount ; 
 int /*<<< orphan*/  dot11RTSFailureCount ; 
 int /*<<< orphan*/  dot11RTSSuccessCount ; 
 int /*<<< orphan*/  failed_count ; 
 int /*<<< orphan*/  frame_duplicate_count ; 
 int /*<<< orphan*/  hwflags ; 
 int /*<<< orphan*/  multicast_received_frame_count ; 
 int /*<<< orphan*/  multicast_transmitted_frame_count ; 
 int /*<<< orphan*/  multiple_retry_count ; 
 int /*<<< orphan*/  power ; 
 int /*<<< orphan*/  queues ; 
 int /*<<< orphan*/  received_fragment_count ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  retry_count ; 
 int /*<<< orphan*/  rx_expand_skb_head ; 
 int /*<<< orphan*/  rx_expand_skb_head2 ; 
 int /*<<< orphan*/  rx_handlers_drop ; 
 int /*<<< orphan*/  rx_handlers_drop_defrag ; 
 int /*<<< orphan*/  rx_handlers_drop_nullfunc ; 
 int /*<<< orphan*/  rx_handlers_drop_short ; 
 int /*<<< orphan*/  rx_handlers_fragments ; 
 int /*<<< orphan*/  rx_handlers_queued ; 
 int /*<<< orphan*/  total_ps_buffered ; 
 int /*<<< orphan*/  transmitted_fragment_count ; 
 int /*<<< orphan*/  transmitted_frame_count ; 
 int /*<<< orphan*/  tx_expand_skb_head ; 
 int /*<<< orphan*/  tx_expand_skb_head_cloned ; 
 int /*<<< orphan*/  tx_handlers_drop ; 
 int /*<<< orphan*/  tx_handlers_drop_fragment ; 
 int /*<<< orphan*/  tx_handlers_drop_not_assoc ; 
 int /*<<< orphan*/  tx_handlers_drop_unauth_port ; 
 int /*<<< orphan*/  tx_handlers_drop_unencrypted ; 
 int /*<<< orphan*/  tx_handlers_drop_wep ; 
 int /*<<< orphan*/  tx_handlers_queued ; 
 int /*<<< orphan*/  tx_status_drop ; 
 int /*<<< orphan*/  user_power ; 
 int /*<<< orphan*/  wep_iv ; 

void debugfs_hw_add(struct ieee80211_local *local)
{
	struct dentry *phyd = local->hw.wiphy->debugfsdir;
	struct dentry *statsd;

	if (!phyd)
		return;

	local->debugfs.keys = debugfs_create_dir("keys", phyd);

	DEBUGFS_ADD(total_ps_buffered);
	DEBUGFS_ADD(wep_iv);
	DEBUGFS_ADD(queues);
#ifdef CONFIG_PM
	DEBUGFS_ADD_MODE(reset, 0200);
#endif
	DEBUGFS_ADD(hwflags);
	DEBUGFS_ADD(user_power);
	DEBUGFS_ADD(power);

	statsd = debugfs_create_dir("statistics", phyd);

	/* if the dir failed, don't put all the other things into the root! */
	if (!statsd)
		return;

	DEBUGFS_STATS_ADD(transmitted_fragment_count,
		local->dot11TransmittedFragmentCount);
	DEBUGFS_STATS_ADD(multicast_transmitted_frame_count,
		local->dot11MulticastTransmittedFrameCount);
	DEBUGFS_STATS_ADD(failed_count, local->dot11FailedCount);
	DEBUGFS_STATS_ADD(retry_count, local->dot11RetryCount);
	DEBUGFS_STATS_ADD(multiple_retry_count,
		local->dot11MultipleRetryCount);
	DEBUGFS_STATS_ADD(frame_duplicate_count,
		local->dot11FrameDuplicateCount);
	DEBUGFS_STATS_ADD(received_fragment_count,
		local->dot11ReceivedFragmentCount);
	DEBUGFS_STATS_ADD(multicast_received_frame_count,
		local->dot11MulticastReceivedFrameCount);
	DEBUGFS_STATS_ADD(transmitted_frame_count,
		local->dot11TransmittedFrameCount);
#ifdef CONFIG_MAC80211_DEBUG_COUNTERS
	DEBUGFS_STATS_ADD(tx_handlers_drop, local->tx_handlers_drop);
	DEBUGFS_STATS_ADD(tx_handlers_queued, local->tx_handlers_queued);
	DEBUGFS_STATS_ADD(tx_handlers_drop_unencrypted,
		local->tx_handlers_drop_unencrypted);
	DEBUGFS_STATS_ADD(tx_handlers_drop_fragment,
		local->tx_handlers_drop_fragment);
	DEBUGFS_STATS_ADD(tx_handlers_drop_wep,
		local->tx_handlers_drop_wep);
	DEBUGFS_STATS_ADD(tx_handlers_drop_not_assoc,
		local->tx_handlers_drop_not_assoc);
	DEBUGFS_STATS_ADD(tx_handlers_drop_unauth_port,
		local->tx_handlers_drop_unauth_port);
	DEBUGFS_STATS_ADD(rx_handlers_drop, local->rx_handlers_drop);
	DEBUGFS_STATS_ADD(rx_handlers_queued, local->rx_handlers_queued);
	DEBUGFS_STATS_ADD(rx_handlers_drop_nullfunc,
		local->rx_handlers_drop_nullfunc);
	DEBUGFS_STATS_ADD(rx_handlers_drop_defrag,
		local->rx_handlers_drop_defrag);
	DEBUGFS_STATS_ADD(rx_handlers_drop_short,
		local->rx_handlers_drop_short);
	DEBUGFS_STATS_ADD(tx_expand_skb_head,
		local->tx_expand_skb_head);
	DEBUGFS_STATS_ADD(tx_expand_skb_head_cloned,
		local->tx_expand_skb_head_cloned);
	DEBUGFS_STATS_ADD(rx_expand_skb_head,
		local->rx_expand_skb_head);
	DEBUGFS_STATS_ADD(rx_expand_skb_head2,
		local->rx_expand_skb_head2);
	DEBUGFS_STATS_ADD(rx_handlers_fragments,
		local->rx_handlers_fragments);
	DEBUGFS_STATS_ADD(tx_status_drop,
		local->tx_status_drop);
#endif
	DEBUGFS_DEVSTATS_ADD(dot11ACKFailureCount);
	DEBUGFS_DEVSTATS_ADD(dot11RTSFailureCount);
	DEBUGFS_DEVSTATS_ADD(dot11FCSErrorCount);
	DEBUGFS_DEVSTATS_ADD(dot11RTSSuccessCount);
}