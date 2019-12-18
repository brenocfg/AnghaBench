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
struct michael_mic_ctx {int l; int r; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int IEEE80211_QOS_CTL_TID_MASK ; 
 int get_unaligned_le16 (int*) ; 
 int get_unaligned_le32 (int const*) ; 
 int* ieee80211_get_DA (struct ieee80211_hdr*) ; 
 int* ieee80211_get_SA (struct ieee80211_hdr*) ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  michael_block (struct michael_mic_ctx*,int) ; 

__attribute__((used)) static void michael_mic_hdr(struct michael_mic_ctx *mctx, const u8 *key,
			    struct ieee80211_hdr *hdr)
{
	u8 *da, *sa, tid;

	da = ieee80211_get_DA(hdr);
	sa = ieee80211_get_SA(hdr);
	if (ieee80211_is_data_qos(hdr->frame_control))
		tid = *ieee80211_get_qos_ctl(hdr) & IEEE80211_QOS_CTL_TID_MASK;
	else
		tid = 0;

	mctx->l = get_unaligned_le32(key);
	mctx->r = get_unaligned_le32(key + 4);

	/*
	 * A pseudo header (DA, SA, Priority, 0, 0, 0) is used in Michael MIC
	 * calculation, but it is _not_ transmitted
	 */
	michael_block(mctx, get_unaligned_le32(da));
	michael_block(mctx, get_unaligned_le16(&da[4]) |
			    (get_unaligned_le16(sa) << 16));
	michael_block(mctx, get_unaligned_le32(&sa[2]));
	michael_block(mctx, tid);
}