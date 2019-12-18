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
struct usbnet {struct asix_common_private* driver_priv; } ;
struct sk_buff {int dummy; } ;
struct asix_rx_fixup_info {int dummy; } ;
struct asix_common_private {struct asix_rx_fixup_info rx_fixup_info; } ;

/* Variables and functions */
 int asix_rx_fixup_internal (struct usbnet*,struct sk_buff*,struct asix_rx_fixup_info*) ; 

int asix_rx_fixup_common(struct usbnet *dev, struct sk_buff *skb)
{
	struct asix_common_private *dp = dev->driver_priv;
	struct asix_rx_fixup_info *rx = &dp->rx_fixup_info;

	return asix_rx_fixup_internal(dev, skb, rx);
}