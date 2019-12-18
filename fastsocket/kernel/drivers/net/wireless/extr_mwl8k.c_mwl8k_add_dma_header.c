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
struct sk_buff {int truesize; int len; scalar_t__ data; } ;
struct mwl8k_priv {TYPE_1__* hw; scalar_t__ ap_fw; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct mwl8k_dma_data {int /*<<< orphan*/  fwlen; struct ieee80211_hdr wh; } ;
struct ieee80211_cts {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IEEE80211_QOS_CTL_LEN ; 
 int REDUCED_TX_HEADROOM ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ieee80211_hdr*,struct ieee80211_hdr*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
mwl8k_add_dma_header(struct mwl8k_priv *priv, struct sk_buff *skb,
						int head_pad, int tail_pad)
{
	struct ieee80211_hdr *wh;
	int hdrlen;
	int reqd_hdrlen;
	struct mwl8k_dma_data *tr;

	/*
	 * Add a firmware DMA header; the firmware requires that we
	 * present a 2-byte payload length followed by a 4-address
	 * header (without QoS field), followed (optionally) by any
	 * WEP/ExtIV header (but only filled in for CCMP).
	 */
	wh = (struct ieee80211_hdr *)skb->data;

	hdrlen = ieee80211_hdrlen(wh->frame_control);

	/*
	 * Check if skb_resize is required because of
	 * tx_headroom adjustment.
	 */
	if (priv->ap_fw && (hdrlen < (sizeof(struct ieee80211_cts)
						+ REDUCED_TX_HEADROOM))) {
		if (pskb_expand_head(skb, REDUCED_TX_HEADROOM, 0, GFP_ATOMIC)) {

			wiphy_err(priv->hw->wiphy,
					"Failed to reallocate TX buffer\n");
			return;
		}
		skb->truesize += REDUCED_TX_HEADROOM;
	}

	reqd_hdrlen = sizeof(*tr) + head_pad;

	if (hdrlen != reqd_hdrlen)
		skb_push(skb, reqd_hdrlen - hdrlen);

	if (ieee80211_is_data_qos(wh->frame_control))
		hdrlen -= IEEE80211_QOS_CTL_LEN;

	tr = (struct mwl8k_dma_data *)skb->data;
	if (wh != &tr->wh)
		memmove(&tr->wh, wh, hdrlen);
	if (hdrlen != sizeof(tr->wh))
		memset(((void *)&tr->wh) + hdrlen, 0, sizeof(tr->wh) - hdrlen);

	/*
	 * Firmware length is the length of the fully formed "802.11
	 * payload".  That is, everything except for the 802.11 header.
	 * This includes all crypto material including the MIC.
	 */
	tr->fwlen = cpu_to_le16(skb->len - sizeof(*tr) + tail_pad);
}