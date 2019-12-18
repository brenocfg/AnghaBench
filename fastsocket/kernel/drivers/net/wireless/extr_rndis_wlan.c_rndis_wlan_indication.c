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
struct usbnet {int /*<<< orphan*/  net; } ;
struct rndis_wlan_private {int /*<<< orphan*/  work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  work_pending; int /*<<< orphan*/  current_command_oid; } ;
struct rndis_indicate {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  OID_802_11_ADD_KEY ; 
#define  RNDIS_STATUS_MEDIA_CONNECT 130 
#define  RNDIS_STATUS_MEDIA_DISCONNECT 129 
#define  RNDIS_STATUS_MEDIA_SPECIFIC_INDICATION 128 
 int /*<<< orphan*/  WORK_LINK_DOWN ; 
 int /*<<< orphan*/  WORK_LINK_UP ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rndis_wlan_media_specific_indication (struct usbnet*,struct rndis_indicate*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbnet_pause_rx (struct usbnet*) ; 

__attribute__((used)) static void rndis_wlan_indication(struct usbnet *usbdev, void *ind, int buflen)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);
	struct rndis_indicate *msg = ind;

	switch (msg->status) {
	case RNDIS_STATUS_MEDIA_CONNECT:
		if (priv->current_command_oid == OID_802_11_ADD_KEY) {
			/* OID_802_11_ADD_KEY causes sometimes extra
			 * "media connect" indications which confuses driver
			 * and userspace to think that device is
			 * roaming/reassociating when it isn't.
			 */
			netdev_dbg(usbdev->net, "ignored OID_802_11_ADD_KEY triggered 'media connect'\n");
			return;
		}

		usbnet_pause_rx(usbdev);

		netdev_info(usbdev->net, "media connect\n");

		/* queue work to avoid recursive calls into rndis_command */
		set_bit(WORK_LINK_UP, &priv->work_pending);
		queue_work(priv->workqueue, &priv->work);
		break;

	case RNDIS_STATUS_MEDIA_DISCONNECT:
		netdev_info(usbdev->net, "media disconnect\n");

		/* queue work to avoid recursive calls into rndis_command */
		set_bit(WORK_LINK_DOWN, &priv->work_pending);
		queue_work(priv->workqueue, &priv->work);
		break;

	case RNDIS_STATUS_MEDIA_SPECIFIC_INDICATION:
		rndis_wlan_media_specific_indication(usbdev, msg, buflen);
		break;

	default:
		netdev_info(usbdev->net, "indication: 0x%08x\n",
			    le32_to_cpu(msg->status));
		break;
	}
}