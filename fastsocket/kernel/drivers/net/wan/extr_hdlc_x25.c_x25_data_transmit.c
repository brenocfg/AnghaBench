#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* xmit ) (struct sk_buff*,struct net_device*) ;} ;
typedef  TYPE_1__ hdlc_device ;

/* Variables and functions */
 TYPE_1__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static void x25_data_transmit(struct net_device *dev, struct sk_buff *skb)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	hdlc->xmit(skb, dev); /* Ignore return value :-( */
}