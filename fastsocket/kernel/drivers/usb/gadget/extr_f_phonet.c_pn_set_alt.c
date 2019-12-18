#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int dummy; } ;
struct usb_function {int dummy; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct phonet_port {int /*<<< orphan*/  lock; struct f_phonet* usb; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {TYPE_2__* config; } ;
struct f_phonet {int /*<<< orphan*/ * out_reqv; TYPE_4__* in_ep; TYPE_4__* out_ep; struct net_device* dev; TYPE_3__ function; } ;
struct TYPE_12__ {unsigned int bInterfaceNumber; } ;
struct TYPE_11__ {unsigned int bInterfaceNumber; } ;
struct TYPE_10__ {struct f_phonet* driver_data; } ;
struct TYPE_8__ {TYPE_1__* cdev; } ;
struct TYPE_7__ {struct usb_gadget* gadget; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __pn_reset (struct usb_function*) ; 
 struct usb_endpoint_descriptor* ep_choose (struct usb_gadget*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct f_phonet* func_to_pn (struct usb_function*) ; 
 struct phonet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int phonet_rxq_size ; 
 TYPE_6__ pn_control_intf_desc ; 
 TYPE_5__ pn_data_intf_desc ; 
 int /*<<< orphan*/  pn_fs_sink_desc ; 
 int /*<<< orphan*/  pn_fs_source_desc ; 
 int /*<<< orphan*/  pn_hs_sink_desc ; 
 int /*<<< orphan*/  pn_hs_source_desc ; 
 int /*<<< orphan*/  pn_rx_submit (struct f_phonet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_enable (TYPE_4__*,struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static int pn_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_phonet *fp = func_to_pn(f);
	struct usb_gadget *gadget = fp->function.config->cdev->gadget;

	if (intf == pn_control_intf_desc.bInterfaceNumber)
		/* control interface, no altsetting */
		return (alt > 0) ? -EINVAL : 0;

	if (intf == pn_data_intf_desc.bInterfaceNumber) {
		struct net_device *dev = fp->dev;
		struct phonet_port *port = netdev_priv(dev);

		/* data intf (0: inactive, 1: active) */
		if (alt > 1)
			return -EINVAL;

		spin_lock(&port->lock);
		__pn_reset(f);
		if (alt == 1) {
			struct usb_endpoint_descriptor *out, *in;
			int i;

			out = ep_choose(gadget,
					&pn_hs_sink_desc,
					&pn_fs_sink_desc);
			in = ep_choose(gadget,
					&pn_hs_source_desc,
					&pn_fs_source_desc);
			usb_ep_enable(fp->out_ep, out);
			usb_ep_enable(fp->in_ep, in);

			port->usb = fp;
			fp->out_ep->driver_data = fp;
			fp->in_ep->driver_data = fp;

			netif_carrier_on(dev);
			for (i = 0; i < phonet_rxq_size; i++)
				pn_rx_submit(fp, fp->out_reqv[i], GFP_ATOMIC);
		}
		spin_unlock(&port->lock);
		return 0;
	}

	return -EINVAL;
}