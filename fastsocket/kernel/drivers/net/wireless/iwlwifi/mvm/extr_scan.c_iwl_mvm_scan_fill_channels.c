#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct iwl_scan_cmd {int channel_count; TYPE_1__ tx_cmd; scalar_t__ data; } ;
struct iwl_scan_channel {void* iteration_count; void* passive_dwell; void* active_dwell; int /*<<< orphan*/  type; void* channel; } ;
struct cfg80211_scan_request {TYPE_2__** channels; int /*<<< orphan*/  n_ssids; } ;
struct TYPE_4__ {int hw_value; int flags; int /*<<< orphan*/  band; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int IEEE80211_CHAN_PASSIVE_SCAN ; 
 scalar_t__ SCAN_CHANNEL_TYPE_ACTIVE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int iwl_mvm_get_active_dwell (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_get_passive_dwell (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_scan_fill_channels(struct iwl_scan_cmd *cmd,
				       struct cfg80211_scan_request *req)
{
	u16 passive_dwell = iwl_mvm_get_passive_dwell(req->channels[0]->band);
	u16 active_dwell = iwl_mvm_get_active_dwell(req->channels[0]->band,
						    req->n_ssids);
	struct iwl_scan_channel *chan = (struct iwl_scan_channel *)
		(cmd->data + le16_to_cpu(cmd->tx_cmd.len));
	int i;

	for (i = 0; i < cmd->channel_count; i++) {
		chan->channel = cpu_to_le16(req->channels[i]->hw_value);
		chan->type = cpu_to_le32(BIT(req->n_ssids) - 1);
		if (req->channels[i]->flags & IEEE80211_CHAN_PASSIVE_SCAN)
			chan->type &= cpu_to_le32(~SCAN_CHANNEL_TYPE_ACTIVE);
		chan->active_dwell = cpu_to_le16(active_dwell);
		chan->passive_dwell = cpu_to_le16(passive_dwell);
		chan->iteration_count = cpu_to_le16(1);
		chan++;
	}
}