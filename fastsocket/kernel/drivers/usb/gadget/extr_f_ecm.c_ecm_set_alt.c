#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;
struct net_device {int dummy; } ;
struct TYPE_14__ {int is_zlp_ok; int /*<<< orphan*/  cdc_filter; void* out; void* in; TYPE_2__* in_ep; } ;
struct TYPE_12__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  notify; } ;
struct TYPE_11__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  notify; } ;
struct f_ecm {unsigned int ctrl_id; unsigned int data_id; TYPE_7__ port; TYPE_4__ fs; TYPE_3__ hs; TYPE_5__* notify; void* notify_desc; } ;
struct TYPE_13__ {struct f_ecm* driver_data; } ;
struct TYPE_10__ {scalar_t__ driver_data; } ;
struct TYPE_9__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*) ; 
 int /*<<< orphan*/  DEFAULT_FILTER ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int PTR_ERR (struct net_device*) ; 
 int /*<<< orphan*/  VDBG (struct usb_composite_dev*,char*,unsigned int) ; 
 int /*<<< orphan*/  ecm_notify (struct f_ecm*) ; 
 void* ep_choose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct f_ecm* func_to_ecm (struct usb_function*) ; 
 scalar_t__ gadget_is_musbhdrc (int /*<<< orphan*/ ) ; 
 scalar_t__ gadget_is_sa1100 (int /*<<< orphan*/ ) ; 
 struct net_device* gether_connect (TYPE_7__*) ; 
 int /*<<< orphan*/  gether_disconnect (TYPE_7__*) ; 
 int /*<<< orphan*/  usb_ep_disable (TYPE_5__*) ; 
 int /*<<< orphan*/  usb_ep_enable (TYPE_5__*,void*) ; 

__attribute__((used)) static int ecm_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_ecm		*ecm = func_to_ecm(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	/* Control interface has only altsetting 0 */
	if (intf == ecm->ctrl_id) {
		if (alt != 0)
			goto fail;

		if (ecm->notify->driver_data) {
			VDBG(cdev, "reset ecm control %d\n", intf);
			usb_ep_disable(ecm->notify);
		} else {
			VDBG(cdev, "init ecm ctrl %d\n", intf);
			ecm->notify_desc = ep_choose(cdev->gadget,
					ecm->hs.notify,
					ecm->fs.notify);
		}
		usb_ep_enable(ecm->notify, ecm->notify_desc);
		ecm->notify->driver_data = ecm;

	/* Data interface has two altsettings, 0 and 1 */
	} else if (intf == ecm->data_id) {
		if (alt > 1)
			goto fail;

		if (ecm->port.in_ep->driver_data) {
			DBG(cdev, "reset ecm\n");
			gether_disconnect(&ecm->port);
		}

		if (!ecm->port.in) {
			DBG(cdev, "init ecm\n");
			ecm->port.in = ep_choose(cdev->gadget,
					ecm->hs.in, ecm->fs.in);
			ecm->port.out = ep_choose(cdev->gadget,
					ecm->hs.out, ecm->fs.out);
		}

		/* CDC Ethernet only sends data in non-default altsettings.
		 * Changing altsettings resets filters, statistics, etc.
		 */
		if (alt == 1) {
			struct net_device	*net;

			/* Enable zlps by default for ECM conformance;
			 * override for musb_hdrc (avoids txdma ovhead)
			 * and sa1100 (can't).
			 */
			ecm->port.is_zlp_ok = !(
				   gadget_is_sa1100(cdev->gadget)
				|| gadget_is_musbhdrc(cdev->gadget)
				);
			ecm->port.cdc_filter = DEFAULT_FILTER;
			DBG(cdev, "activate ecm\n");
			net = gether_connect(&ecm->port);
			if (IS_ERR(net))
				return PTR_ERR(net);
		}

		/* NOTE this can be a minor disagreement with the ECM spec,
		 * which says speed notifications will "always" follow
		 * connection notifications.  But we allow one connect to
		 * follow another (if the first is in flight), and instead
		 * just guarantee that a speed notification is always sent.
		 */
		ecm_notify(ecm);
	} else
		goto fail;

	return 0;
fail:
	return -EINVAL;
}