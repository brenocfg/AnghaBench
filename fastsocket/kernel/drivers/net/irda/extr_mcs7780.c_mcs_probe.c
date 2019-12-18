#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_4__* cur_altsetting; int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  devnum; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  bits; } ;
struct TYPE_7__ {int bits; } ;
struct TYPE_11__ {TYPE_2__ min_turn_time; TYPE_1__ baud_rate; } ;
struct mcs_cb {int /*<<< orphan*/  receive_mode; int /*<<< orphan*/  sir_tweak; int /*<<< orphan*/  transceiver_type; int /*<<< orphan*/  work; TYPE_5__ qos; int /*<<< orphan*/  lock; struct net_device* netdev; struct usb_device* usbdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  bNumEndpoints; } ;
struct TYPE_10__ {TYPE_3__ desc; int /*<<< orphan*/  endpoint; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRDA_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRDA_ERROR (char*) ; 
 int IR_115200 ; 
 int IR_1152000 ; 
 int IR_19200 ; 
 int IR_2400 ; 
 int IR_38400 ; 
 int IR_4000000 ; 
 int IR_57600 ; 
 int IR_576000 ; 
 int IR_9600 ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_irdadev (int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  irda_init_max_qos_capabilies (TYPE_5__*) ; 
 int /*<<< orphan*/  irda_qos_bits_to_value (TYPE_5__*) ; 
 int mcs_find_endpoints (struct mcs_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs_netdev_ops ; 
 int /*<<< orphan*/  mcs_speed_work ; 
 struct mcs_cb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qos_mtt_bits ; 
 int /*<<< orphan*/  receive_mode ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  sir_tweak ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transceiver_type ; 
 int usb_reset_configuration (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct mcs_cb*) ; 

__attribute__((used)) static int mcs_probe(struct usb_interface *intf,
		     const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct net_device *ndev = NULL;
	struct mcs_cb *mcs;
	int ret = -ENOMEM;

	ndev = alloc_irdadev(sizeof(*mcs));
	if (!ndev)
		goto error1;

	IRDA_DEBUG(1, "MCS7780 USB-IrDA bridge found at %d.\n", udev->devnum);

	SET_NETDEV_DEV(ndev, &intf->dev);

	ret = usb_reset_configuration(udev);
	if (ret != 0) {
		IRDA_ERROR("mcs7780: usb reset configuration failed\n");
		goto error2;
	}

	mcs = netdev_priv(ndev);
	mcs->usbdev = udev;
	mcs->netdev = ndev;
	spin_lock_init(&mcs->lock);

	/* Initialize QoS for this device */
	irda_init_max_qos_capabilies(&mcs->qos);

	/* That's the Rx capability. */
	mcs->qos.baud_rate.bits &=
	    IR_2400 | IR_9600 | IR_19200 | IR_38400 | IR_57600 | IR_115200
		| IR_576000 | IR_1152000 | (IR_4000000 << 8);


	mcs->qos.min_turn_time.bits &= qos_mtt_bits;
	irda_qos_bits_to_value(&mcs->qos);

	/* Speed change work initialisation*/
	INIT_WORK(&mcs->work, mcs_speed_work);

	ndev->netdev_ops = &mcs_netdev_ops;

	if (!intf->cur_altsetting)
		goto error2;

	ret = mcs_find_endpoints(mcs, intf->cur_altsetting->endpoint,
				 intf->cur_altsetting->desc.bNumEndpoints);
	if (!ret) {
		ret = -ENODEV;
		goto error2;
	}

	ret = register_netdev(ndev);
	if (ret != 0)
		goto error2;

	IRDA_DEBUG(1, "IrDA: Registered MosChip MCS7780 device as %s\n",
		   ndev->name);

	mcs->transceiver_type = transceiver_type;
	mcs->sir_tweak = sir_tweak;
	mcs->receive_mode = receive_mode;

	usb_set_intfdata(intf, mcs);
	return 0;

	error2:
		free_netdev(ndev);

	error1:
		return ret;
}