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
struct urb {int /*<<< orphan*/  dev; struct sk_buff* context; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  p54_free_skb (struct ieee80211_hw*,struct sk_buff*) ; 
 struct ieee80211_hw* usb_get_intfdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ifnum_to_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p54u_tx_cb(struct urb *urb)
{
	struct sk_buff *skb = urb->context;
	struct ieee80211_hw *dev =
		usb_get_intfdata(usb_ifnum_to_if(urb->dev, 0));

	p54_free_skb(dev, skb);
}