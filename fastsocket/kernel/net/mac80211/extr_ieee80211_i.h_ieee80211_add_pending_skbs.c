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
struct sk_buff_head {int dummy; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_add_pending_skbs_fn (struct ieee80211_local*,struct sk_buff_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ieee80211_add_pending_skbs(struct ieee80211_local *local,
					      struct sk_buff_head *skbs)
{
	ieee80211_add_pending_skbs_fn(local, skbs, NULL, NULL);
}