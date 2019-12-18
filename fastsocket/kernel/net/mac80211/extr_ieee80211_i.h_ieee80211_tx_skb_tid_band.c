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
struct sk_buff {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  __ieee80211_tx_skb_tid_band (struct ieee80211_sub_if_data*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline void
ieee80211_tx_skb_tid_band(struct ieee80211_sub_if_data *sdata,
			  struct sk_buff *skb, int tid,
			  enum ieee80211_band band)
{
	rcu_read_lock();
	__ieee80211_tx_skb_tid_band(sdata, skb, tid, band);
	rcu_read_unlock();
}