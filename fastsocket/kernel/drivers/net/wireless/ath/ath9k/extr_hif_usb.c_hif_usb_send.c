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
struct sk_buff {int dummy; } ;
struct hif_device_usb {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_REG_OUT_PIPE 129 
#define  USB_WLAN_TX_PIPE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hif_usb_send_regout (struct hif_device_usb*,struct sk_buff*) ; 
 int hif_usb_send_tx (struct hif_device_usb*,struct sk_buff*) ; 

__attribute__((used)) static int hif_usb_send(void *hif_handle, u8 pipe_id, struct sk_buff *skb)
{
	struct hif_device_usb *hif_dev = (struct hif_device_usb *)hif_handle;
	int ret = 0;

	switch (pipe_id) {
	case USB_WLAN_TX_PIPE:
		ret = hif_usb_send_tx(hif_dev, skb);
		break;
	case USB_REG_OUT_PIPE:
		ret = hif_usb_send_regout(hif_dev, skb);
		break;
	default:
		dev_err(&hif_dev->udev->dev,
			"ath9k_htc: Invalid TX pipe: %d\n", pipe_id);
		ret = -EINVAL;
		break;
	}

	return ret;
}