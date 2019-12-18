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
struct wbsoft_priv {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ieee80211_hw {struct wbsoft_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_TYPE_802_11_MANAGEMENT ; 
 int /*<<< orphan*/  MLMESendFrame (struct wbsoft_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NETDEV_TX_OK ; 

__attribute__((used)) static int wbsoft_tx(struct ieee80211_hw *dev, struct sk_buff *skb)
{
	struct wbsoft_priv *priv = dev->priv;

	MLMESendFrame(priv, skb->data, skb->len, FRAME_TYPE_802_11_MANAGEMENT);

	return NETDEV_TX_OK;
}