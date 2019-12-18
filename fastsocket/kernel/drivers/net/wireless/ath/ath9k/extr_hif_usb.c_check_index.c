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
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct ath9k_htc_tx_ctl {scalar_t__ type; scalar_t__ sta_idx; } ;

/* Variables and functions */
 scalar_t__ ATH9K_HTC_AMPDU ; 
 struct ath9k_htc_tx_ctl* HTC_SKB_CB (struct sk_buff*) ; 

__attribute__((used)) static inline bool check_index(struct sk_buff *skb, u8 idx)
{
	struct ath9k_htc_tx_ctl *tx_ctl;

	tx_ctl = HTC_SKB_CB(skb);

	if ((tx_ctl->type == ATH9K_HTC_AMPDU) &&
	    (tx_ctl->sta_idx == idx))
		return true;

	return false;
}