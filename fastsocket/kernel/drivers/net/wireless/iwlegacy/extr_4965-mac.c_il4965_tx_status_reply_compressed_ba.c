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
typedef  int u64 ;
typedef  int u16 ;
struct il_priv {TYPE_1__* txq; } ;
struct il_ht_agg {int start_idx; int frame_count; int bitmap; int /*<<< orphan*/  rate_n_flags; scalar_t__ wait_for_ba; } ;
struct il_compressed_ba_resp {int bitmap; int /*<<< orphan*/  seq_ctl; int /*<<< orphan*/  scd_flow; } ;
struct TYPE_4__ {int ampdu_ack_len; int ampdu_len; } ;
struct ieee80211_tx_info {TYPE_2__ status; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/ * skbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TX_REPLY (char*,...) ; 
 int EINVAL ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_AMPDU ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int SEQ_TO_IDX (int) ; 
 int /*<<< orphan*/  il4965_hwrate_to_tx_control (struct il_priv*,int /*<<< orphan*/ ,struct ieee80211_tx_info*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
il4965_tx_status_reply_compressed_ba(struct il_priv *il, struct il_ht_agg *agg,
				     struct il_compressed_ba_resp *ba_resp)
{
	int i, sh, ack;
	u16 seq_ctl = le16_to_cpu(ba_resp->seq_ctl);
	u16 scd_flow = le16_to_cpu(ba_resp->scd_flow);
	int successes = 0;
	struct ieee80211_tx_info *info;
	u64 bitmap, sent_bitmap;

	if (unlikely(!agg->wait_for_ba)) {
		if (unlikely(ba_resp->bitmap))
			IL_ERR("Received BA when not expected\n");
		return -EINVAL;
	}

	/* Mark that the expected block-ack response arrived */
	agg->wait_for_ba = 0;
	D_TX_REPLY("BA %d %d\n", agg->start_idx, ba_resp->seq_ctl);

	/* Calculate shift to align block-ack bits with our Tx win bits */
	sh = agg->start_idx - SEQ_TO_IDX(seq_ctl >> 4);
	if (sh < 0)		/* tbw something is wrong with indices */
		sh += 0x100;

	if (agg->frame_count > (64 - sh)) {
		D_TX_REPLY("more frames than bitmap size");
		return -1;
	}

	/* don't use 64-bit values for now */
	bitmap = le64_to_cpu(ba_resp->bitmap) >> sh;

	/* check for success or failure according to the
	 * transmitted bitmap and block-ack bitmap */
	sent_bitmap = bitmap & agg->bitmap;

	/* For each frame attempted in aggregation,
	 * update driver's record of tx frame's status. */
	i = 0;
	while (sent_bitmap) {
		ack = sent_bitmap & 1ULL;
		successes += ack;
		D_TX_REPLY("%s ON i=%d idx=%d raw=%d\n", ack ? "ACK" : "NACK",
			   i, (agg->start_idx + i) & 0xff, agg->start_idx + i);
		sent_bitmap >>= 1;
		++i;
	}

	D_TX_REPLY("Bitmap %llx\n", (unsigned long long)bitmap);

	info = IEEE80211_SKB_CB(il->txq[scd_flow].skbs[agg->start_idx]);
	memset(&info->status, 0, sizeof(info->status));
	info->flags |= IEEE80211_TX_STAT_ACK;
	info->flags |= IEEE80211_TX_STAT_AMPDU;
	info->status.ampdu_ack_len = successes;
	info->status.ampdu_len = agg->frame_count;
	il4965_hwrate_to_tx_control(il, agg->rate_n_flags, info);

	return 0;
}