#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
struct txentry_desc {int dummy; } ;
struct rt2x00_dev {TYPE_3__* ops; int /*<<< orphan*/  dev; } ;
struct queue_entry_priv_usb_bcn {int /*<<< orphan*/  guardian_urb; scalar_t__ guardian_data; int /*<<< orphan*/  urb; } ;
struct queue_entry {TYPE_4__* skb; TYPE_1__* queue; struct queue_entry_priv_usb_bcn* priv_data; } ;
struct TYPE_9__ {scalar_t__* data; } ;
struct TYPE_8__ {TYPE_2__* lib; } ;
struct TYPE_7__ {int (* get_tx_data_len ) (struct queue_entry*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  usb_endpoint; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_FRAME_BEACON ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TXD_DESC_SIZE ; 
 int /*<<< orphan*/  TXRX_CSR19 ; 
 int /*<<< orphan*/  TXRX_CSR19_BEACON_GEN ; 
 int /*<<< orphan*/  TXRX_CSR19_TBCN ; 
 int /*<<< orphan*/  TXRX_CSR19_TSF_COUNT ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_beacondone ; 
 int /*<<< orphan*/  rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_write_tx_desc (struct queue_entry*,struct txentry_desc*) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00debug_dump_frame (struct rt2x00_dev*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  skb_push (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int stub1 (struct queue_entry*) ; 
 struct usb_device* to_usb_device_intf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,int,scalar_t__*,int,int /*<<< orphan*/ ,struct queue_entry*) ; 
 int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2500usb_write_beacon(struct queue_entry *entry,
				   struct txentry_desc *txdesc)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	struct usb_device *usb_dev = to_usb_device_intf(rt2x00dev->dev);
	struct queue_entry_priv_usb_bcn *bcn_priv = entry->priv_data;
	int pipe = usb_sndbulkpipe(usb_dev, entry->queue->usb_endpoint);
	int length;
	u16 reg, reg0;

	/*
	 * Disable beaconing while we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	rt2500usb_register_read(rt2x00dev, TXRX_CSR19, &reg);
	rt2x00_set_field16(&reg, TXRX_CSR19_BEACON_GEN, 0);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR19, reg);

	/*
	 * Add space for the descriptor in front of the skb.
	 */
	skb_push(entry->skb, TXD_DESC_SIZE);
	memset(entry->skb->data, 0, TXD_DESC_SIZE);

	/*
	 * Write the TX descriptor for the beacon.
	 */
	rt2500usb_write_tx_desc(entry, txdesc);

	/*
	 * Dump beacon to userspace through debugfs.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_BEACON, entry->skb);

	/*
	 * USB devices cannot blindly pass the skb->len as the
	 * length of the data to usb_fill_bulk_urb. Pass the skb
	 * to the driver to determine what the length should be.
	 */
	length = rt2x00dev->ops->lib->get_tx_data_len(entry);

	usb_fill_bulk_urb(bcn_priv->urb, usb_dev, pipe,
			  entry->skb->data, length, rt2500usb_beacondone,
			  entry);

	/*
	 * Second we need to create the guardian byte.
	 * We only need a single byte, so lets recycle
	 * the 'flags' field we are not using for beacons.
	 */
	bcn_priv->guardian_data = 0;
	usb_fill_bulk_urb(bcn_priv->guardian_urb, usb_dev, pipe,
			  &bcn_priv->guardian_data, 1, rt2500usb_beacondone,
			  entry);

	/*
	 * Send out the guardian byte.
	 */
	usb_submit_urb(bcn_priv->guardian_urb, GFP_ATOMIC);

	/*
	 * Enable beaconing again.
	 */
	rt2x00_set_field16(&reg, TXRX_CSR19_TSF_COUNT, 1);
	rt2x00_set_field16(&reg, TXRX_CSR19_TBCN, 1);
	reg0 = reg;
	rt2x00_set_field16(&reg, TXRX_CSR19_BEACON_GEN, 1);
	/*
	 * Beacon generation will fail initially.
	 * To prevent this we need to change the TXRX_CSR19
	 * register several times (reg0 is the same as reg
	 * except for TXRX_CSR19_BEACON_GEN, which is 0 in reg0
	 * and 1 in reg).
	 */
	rt2500usb_register_write(rt2x00dev, TXRX_CSR19, reg);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR19, reg0);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR19, reg);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR19, reg0);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR19, reg);
}