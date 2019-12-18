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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {size_t priority; } ;
struct ieee80211_sub_if_data {int wmm_acm; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int /*<<< orphan*/ * ieee802_1d_to_ac ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wme_downgrade_ac (struct sk_buff*) ; 

__attribute__((used)) static u16 ieee80211_downgrade_queue(struct ieee80211_sub_if_data *sdata,
				     struct sk_buff *skb)
{
	/* in case we are a client verify acm is not set for this ac */
	while (unlikely(sdata->wmm_acm & BIT(skb->priority))) {
		if (wme_downgrade_ac(skb)) {
			/*
			 * This should not really happen. The AP has marked all
			 * lower ACs to require admission control which is not
			 * a reasonable configuration. Allow the frame to be
			 * transmitted using AC_BK as a workaround.
			 */
			break;
		}
	}

	/* look up which queue to use for frames with this 1d tag */
	return ieee802_1d_to_ac[skb->priority];
}