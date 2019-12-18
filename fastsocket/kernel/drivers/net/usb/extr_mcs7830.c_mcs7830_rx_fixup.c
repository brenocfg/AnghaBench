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
typedef  int u8 ;
struct usbnet {TYPE_1__* udev; } ;
struct sk_buff {int len; int* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int mcs7830_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	u8 status;

	if (skb->len == 0) {
		dev_err(&dev->udev->dev, "unexpected empty rx frame\n");
		return 0;
	}

	skb_trim(skb, skb->len - 1);
	status = skb->data[skb->len];

	if (status != 0x20)
		dev_dbg(&dev->udev->dev, "rx fixup status %x\n", status);

	return skb->len > 0;
}