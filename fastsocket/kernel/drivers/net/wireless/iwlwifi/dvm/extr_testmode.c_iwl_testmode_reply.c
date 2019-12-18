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
struct iwl_op_mode {int dummy; } ;

/* Variables and functions */
 int cfg80211_testmode_reply (struct sk_buff*) ; 

__attribute__((used)) static int iwl_testmode_reply(struct iwl_op_mode *op_mode, struct sk_buff *skb)
{
	return cfg80211_testmode_reply(skb);
}