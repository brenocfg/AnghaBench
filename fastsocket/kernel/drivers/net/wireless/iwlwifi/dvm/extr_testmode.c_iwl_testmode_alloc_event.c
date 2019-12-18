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
struct sk_buff {int dummy; } ;
struct iwl_priv {TYPE_1__* hw; } ;
struct iwl_op_mode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct iwl_priv* IWL_OP_MODE_GET_DVM (struct iwl_op_mode*) ; 
 struct sk_buff* cfg80211_testmode_alloc_event_skb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *iwl_testmode_alloc_event(struct iwl_op_mode *op_mode,
						int len)
{
	struct iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);
	return cfg80211_testmode_alloc_event_skb(priv->hw->wiphy, len,
						 GFP_ATOMIC);
}