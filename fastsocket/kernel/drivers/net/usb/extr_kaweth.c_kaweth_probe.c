#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bcdDevice; scalar_t__ bDescriptorType; scalar_t__ bLength; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; int /*<<< orphan*/  devnum; } ;
struct net_device {int mtu; int name; int /*<<< orphan*/  features; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; } ;
struct TYPE_6__ {int statistics_mask; int max_multicast_filters; int /*<<< orphan*/  segment_size; scalar_t__* const hw_addr; } ;
struct kaweth_device {void* tx_urb; void* rx_urb; void* irq_urb; int /*<<< orphan*/  intbufferhandle; void* intbuffer; struct usb_device* dev; int /*<<< orphan*/  rxbufferhandle; void* rx_buf; struct net_device* net; int /*<<< orphan*/  lowmem_work; TYPE_3__ configuration; struct usb_interface* intf; int /*<<< orphan*/ * firmware_buf; int /*<<< orphan*/  term_wait; int /*<<< orphan*/  device_lock; } ;
typedef  scalar_t__* eth_addr_t ;
typedef  int /*<<< orphan*/  bcast_addr ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTBUFFERSIZE ; 
 int /*<<< orphan*/  KAWETH_BUF_SIZE ; 
 int KAWETH_PACKET_FILTER_BROADCAST ; 
 int KAWETH_PACKET_FILTER_DIRECTED ; 
 int KAWETH_PACKET_FILTER_MULTICAST ; 
 int /*<<< orphan*/  KAWETH_SOFS_TO_WAIT ; 
 int /*<<< orphan*/  KAWETH_TX_TIMEOUT ; 
 int /*<<< orphan*/  NETIF_F_HIGHDMA ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ dma_supported (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int kaweth_download_firmware (struct kaweth_device*,char*,int,int) ; 
 int /*<<< orphan*/  kaweth_netdev_ops ; 
 int kaweth_read_configuration (struct kaweth_device*) ; 
 int /*<<< orphan*/  kaweth_reset (struct kaweth_device*) ; 
 int /*<<< orphan*/  kaweth_resubmit_tl ; 
 int kaweth_set_receive_filter (struct kaweth_device*,int) ; 
 scalar_t__ kaweth_set_sofs_wait (struct kaweth_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ kaweth_set_urb_size (struct kaweth_device*,int /*<<< orphan*/ ) ; 
 int kaweth_trigger_firmware (struct kaweth_device*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (scalar_t__* const*,scalar_t__* const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__* const*,int) ; 
 struct kaweth_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ops ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* usb_buffer_alloc (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (void*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct kaweth_device*) ; 

__attribute__((used)) static int kaweth_probe(
		struct usb_interface *intf,
		const struct usb_device_id *id      /* from id_table */
	)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct kaweth_device *kaweth;
	struct net_device *netdev;
	const eth_addr_t bcast_addr = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	int result = 0;

	dbg("Kawasaki Device Probe (Device number:%d): 0x%4.4x:0x%4.4x:0x%4.4x",
		 dev->devnum,
		 le16_to_cpu(dev->descriptor.idVendor),
		 le16_to_cpu(dev->descriptor.idProduct),
		 le16_to_cpu(dev->descriptor.bcdDevice));

	dbg("Device at %p", dev);

	dbg("Descriptor length: %x type: %x",
		 (int)dev->descriptor.bLength,
		 (int)dev->descriptor.bDescriptorType);

	netdev = alloc_etherdev(sizeof(*kaweth));
	if (!netdev)
		return -ENOMEM;

	kaweth = netdev_priv(netdev);
	kaweth->dev = dev;
	kaweth->net = netdev;

	spin_lock_init(&kaweth->device_lock);
	init_waitqueue_head(&kaweth->term_wait);

	dbg("Resetting.");

	kaweth_reset(kaweth);

	/*
	 * If high byte of bcdDevice is nonzero, firmware is already
	 * downloaded. Don't try to do it again, or we'll hang the device.
	 */

	if (le16_to_cpu(dev->descriptor.bcdDevice) >> 8) {
		dev_info(&intf->dev, "Firmware present in device.\n");
	} else {
		/* Download the firmware */
		dev_info(&intf->dev, "Downloading firmware...\n");
		kaweth->firmware_buf = (__u8 *)__get_free_page(GFP_KERNEL);
		if ((result = kaweth_download_firmware(kaweth,
						      "kaweth/new_code.bin",
						      100,
						      2)) < 0) {
			err("Error downloading firmware (%d)", result);
			goto err_fw;
		}

		if ((result = kaweth_download_firmware(kaweth,
						      "kaweth/new_code_fix.bin",
						      100,
						      3)) < 0) {
			err("Error downloading firmware fix (%d)", result);
			goto err_fw;
		}

		if ((result = kaweth_download_firmware(kaweth,
						      "kaweth/trigger_code.bin",
						      126,
						      2)) < 0) {
			err("Error downloading trigger code (%d)", result);
			goto err_fw;

		}

		if ((result = kaweth_download_firmware(kaweth,
						      "kaweth/trigger_code_fix.bin",
						      126,
						      3)) < 0) {
			err("Error downloading trigger code fix (%d)", result);
			goto err_fw;
		}


		if ((result = kaweth_trigger_firmware(kaweth, 126)) < 0) {
			err("Error triggering firmware (%d)", result);
			goto err_fw;
		}

		/* Device will now disappear for a moment...  */
		dev_info(&intf->dev, "Firmware loaded.  I'll be back...\n");
err_fw:
		free_page((unsigned long)kaweth->firmware_buf);
		free_netdev(netdev);
		return -EIO;
	}

	result = kaweth_read_configuration(kaweth);

	if(result < 0) {
		err("Error reading configuration (%d), no net device created", result);
		goto err_free_netdev;
	}

	dev_info(&intf->dev, "Statistics collection: %x\n", kaweth->configuration.statistics_mask);
	dev_info(&intf->dev, "Multicast filter limit: %x\n", kaweth->configuration.max_multicast_filters & ((1 << 15) - 1));
	dev_info(&intf->dev, "MTU: %d\n", le16_to_cpu(kaweth->configuration.segment_size));
	dev_info(&intf->dev, "Read MAC address %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n",
		 (int)kaweth->configuration.hw_addr[0],
		 (int)kaweth->configuration.hw_addr[1],
		 (int)kaweth->configuration.hw_addr[2],
		 (int)kaweth->configuration.hw_addr[3],
		 (int)kaweth->configuration.hw_addr[4],
		 (int)kaweth->configuration.hw_addr[5]);

	if(!memcmp(&kaweth->configuration.hw_addr,
                   &bcast_addr,
		   sizeof(bcast_addr))) {
		err("Firmware not functioning properly, no net device created");
		goto err_free_netdev;
	}

	if(kaweth_set_urb_size(kaweth, KAWETH_BUF_SIZE) < 0) {
		dbg("Error setting URB size");
		goto err_free_netdev;
	}

	if(kaweth_set_sofs_wait(kaweth, KAWETH_SOFS_TO_WAIT) < 0) {
		err("Error setting SOFS wait");
		goto err_free_netdev;
	}

	result = kaweth_set_receive_filter(kaweth,
                                           KAWETH_PACKET_FILTER_DIRECTED |
                                           KAWETH_PACKET_FILTER_BROADCAST |
                                           KAWETH_PACKET_FILTER_MULTICAST);

	if(result < 0) {
		err("Error setting receive filter");
		goto err_free_netdev;
	}

	dbg("Initializing net device.");

	kaweth->intf = intf;

	kaweth->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!kaweth->tx_urb)
		goto err_free_netdev;
	kaweth->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!kaweth->rx_urb)
		goto err_only_tx;
	kaweth->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!kaweth->irq_urb)
		goto err_tx_and_rx;

	kaweth->intbuffer = usb_buffer_alloc(	kaweth->dev,
						INTBUFFERSIZE,
						GFP_KERNEL,
						&kaweth->intbufferhandle);
	if (!kaweth->intbuffer)
		goto err_tx_and_rx_and_irq;
	kaweth->rx_buf = usb_buffer_alloc(	kaweth->dev,
						KAWETH_BUF_SIZE,
						GFP_KERNEL,
						&kaweth->rxbufferhandle);
	if (!kaweth->rx_buf)
		goto err_all_but_rxbuf;

	memcpy(netdev->broadcast, &bcast_addr, sizeof(bcast_addr));
	memcpy(netdev->dev_addr, &kaweth->configuration.hw_addr,
               sizeof(kaweth->configuration.hw_addr));

	netdev->netdev_ops = &kaweth_netdev_ops;
	netdev->watchdog_timeo = KAWETH_TX_TIMEOUT;
	netdev->mtu = le16_to_cpu(kaweth->configuration.segment_size);
	SET_ETHTOOL_OPS(netdev, &ops);

	/* kaweth is zeroed as part of alloc_netdev */
	INIT_DELAYED_WORK(&kaweth->lowmem_work, kaweth_resubmit_tl);
	usb_set_intfdata(intf, kaweth);

#if 0
// dma_supported() is deeply broken on almost all architectures
	if (dma_supported (&intf->dev, 0xffffffffffffffffULL))
		kaweth->net->features |= NETIF_F_HIGHDMA;
#endif

	SET_NETDEV_DEV(netdev, &intf->dev);
	if (register_netdev(netdev) != 0) {
		err("Error registering netdev.");
		goto err_intfdata;
	}

	dev_info(&intf->dev, "kaweth interface created at %s\n",
		 kaweth->net->name);

	dbg("Kaweth probe returning.");

	return 0;

err_intfdata:
	usb_set_intfdata(intf, NULL);
	usb_buffer_free(kaweth->dev, KAWETH_BUF_SIZE, (void *)kaweth->rx_buf, kaweth->rxbufferhandle);
err_all_but_rxbuf:
	usb_buffer_free(kaweth->dev, INTBUFFERSIZE, (void *)kaweth->intbuffer, kaweth->intbufferhandle);
err_tx_and_rx_and_irq:
	usb_free_urb(kaweth->irq_urb);
err_tx_and_rx:
	usb_free_urb(kaweth->rx_urb);
err_only_tx:
	usb_free_urb(kaweth->tx_urb);
err_free_netdev:
	free_netdev(netdev);

	return -EIO;
}