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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; } ;
struct ieee80211_hdr {int* addr1; int /*<<< orphan*/  addr2; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_KEYTYPE_GROUP ; 
 int /*<<< orphan*/  NL80211_KEYTYPE_PAIRWISE ; 
 int /*<<< orphan*/  cfg80211_michael_mic_failure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void mac80211_ev_michael_mic_failure(struct ieee80211_sub_if_data *sdata, int keyidx,
				     struct ieee80211_hdr *hdr, const u8 *tsc,
				     gfp_t gfp)
{
	cfg80211_michael_mic_failure(sdata->dev, hdr->addr2,
				     (hdr->addr1[0] & 0x01) ?
				     NL80211_KEYTYPE_GROUP :
				     NL80211_KEYTYPE_PAIRWISE,
				     keyidx, tsc, gfp);
}