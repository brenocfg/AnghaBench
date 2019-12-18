#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct alauda {int /*<<< orphan*/  kref; int /*<<< orphan*/  port; int /*<<< orphan*/  card_mutex; int /*<<< orphan*/  dev; void* bulk_out; int /*<<< orphan*/  bulk_in; void* write_out; struct usb_interface* interface; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALAUDA_PORT_SM ; 
 int /*<<< orphan*/  ALAUDA_PORT_XD ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alauda_check_media (struct alauda*) ; 
 int /*<<< orphan*/  alauda_delete ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct alauda* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct alauda*,struct alauda*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_is_bulk_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_bulk_out (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct alauda*) ; 
 void* usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alauda_probe(struct usb_interface *interface,
		const struct usb_device_id *id)
{
	struct alauda *al;
	struct usb_host_interface *iface;
	struct usb_endpoint_descriptor *ep,
			*ep_in=NULL, *ep_out=NULL, *ep_wr=NULL;
	int i, err = -ENOMEM;

	al = kzalloc(2*sizeof(*al), GFP_KERNEL);
	if (!al)
		goto error;

	kref_init(&al->kref);
	usb_set_intfdata(interface, al);

	al->dev = usb_get_dev(interface_to_usbdev(interface));
	al->interface = interface;

	iface = interface->cur_altsetting;
	for (i = 0; i < iface->desc.bNumEndpoints; ++i) {
		ep = &iface->endpoint[i].desc;

		if (usb_endpoint_is_bulk_in(ep)) {
			ep_in = ep;
		} else if (usb_endpoint_is_bulk_out(ep)) {
			if (i==0)
				ep_wr = ep;
			else
				ep_out = ep;
		}
	}
	err = -EIO;
	if (!ep_wr || !ep_in || !ep_out)
		goto error;

	al->write_out = usb_sndbulkpipe(al->dev,
			usb_endpoint_num(ep_wr));
	al->bulk_in = usb_rcvbulkpipe(al->dev,
			usb_endpoint_num(ep_in));
	al->bulk_out = usb_sndbulkpipe(al->dev,
			usb_endpoint_num(ep_out));

	/* second device is identical up to now */
	memcpy(al+1, al, sizeof(*al));

	mutex_init(&al[0].card_mutex);
	mutex_init(&al[1].card_mutex);

	al[0].port = ALAUDA_PORT_XD;
	al[1].port = ALAUDA_PORT_SM;

	dev_info(&interface->dev, "alauda probed\n");
	alauda_check_media(al);
	alauda_check_media(al+1);

	return 0;

error:
	if (al)
		kref_put(&al->kref, alauda_delete);
	return err;
}