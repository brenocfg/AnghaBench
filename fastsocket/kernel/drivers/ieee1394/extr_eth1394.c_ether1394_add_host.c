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
typedef  scalar_t__ u64 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int broadcast_channel; } ;
struct hpsb_host {TYPE_1__ csr; int /*<<< orphan*/  id; int /*<<< orphan*/  device; } ;
struct eth1394_priv {int broadcast_channel; struct net_device* wake_dev; int /*<<< orphan*/  wake; scalar_t__ local_fifo; struct hpsb_host* host; int /*<<< orphan*/  lock; int /*<<< orphan*/  ip_node_list; } ;
struct eth1394_host_info {struct net_device* dev; struct hpsb_host* host; } ;

/* Variables and functions */
 scalar_t__ CSR1212_INVALID_ADDR_SPACE ; 
 int /*<<< orphan*/  ETH1394_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH1394_PRINT_G (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ETHER1394_REGION_ADDR_LEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_ops ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth1394_highlevel ; 
 int /*<<< orphan*/  ether1394_init_dev ; 
 int /*<<< orphan*/  ether1394_recv_init (struct eth1394_priv*) ; 
 int /*<<< orphan*/  ether1394_reset_priv (struct net_device*,int) ; 
 int /*<<< orphan*/  ether1394_wake_queue ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ hpsb_allocate_and_register_addrspace (int /*<<< orphan*/ *,struct hpsb_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ hpsb_config_rom_ip1394_add (struct hpsb_host*) ; 
 int /*<<< orphan*/  hpsb_config_rom_ip1394_remove (struct hpsb_host*) ; 
 struct eth1394_host_info* hpsb_create_hostinfo (int /*<<< orphan*/ *,struct hpsb_host*,int) ; 
 int /*<<< orphan*/  hpsb_destroy_hostinfo (int /*<<< orphan*/ *,struct hpsb_host*) ; 
 int /*<<< orphan*/  hpsb_unregister_addrspace (int /*<<< orphan*/ *,struct hpsb_host*,scalar_t__) ; 
 struct eth1394_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ether1394_add_host(struct hpsb_host *host)
{
	struct eth1394_host_info *hi = NULL;
	struct net_device *dev = NULL;
	struct eth1394_priv *priv;
	u64 fifo_addr;

	if (hpsb_config_rom_ip1394_add(host) != 0) {
		ETH1394_PRINT_G(KERN_ERR, "Can't add IP-over-1394 ROM entry\n");
		return;
	}

	fifo_addr = hpsb_allocate_and_register_addrspace(
			&eth1394_highlevel, host, &addr_ops,
			ETHER1394_REGION_ADDR_LEN, ETHER1394_REGION_ADDR_LEN,
			CSR1212_INVALID_ADDR_SPACE, CSR1212_INVALID_ADDR_SPACE);
	if (fifo_addr == CSR1212_INVALID_ADDR_SPACE) {
		ETH1394_PRINT_G(KERN_ERR, "Cannot register CSR space\n");
		hpsb_config_rom_ip1394_remove(host);
		return;
	}

	dev = alloc_netdev(sizeof(*priv), "eth%d", ether1394_init_dev);
	if (dev == NULL) {
		ETH1394_PRINT_G(KERN_ERR, "Out of memory\n");
		goto out;
	}

	SET_NETDEV_DEV(dev, &host->device);

	priv = netdev_priv(dev);
	INIT_LIST_HEAD(&priv->ip_node_list);
	spin_lock_init(&priv->lock);
	priv->host = host;
	priv->local_fifo = fifo_addr;
	INIT_WORK(&priv->wake, ether1394_wake_queue);
	priv->wake_dev = dev;

	hi = hpsb_create_hostinfo(&eth1394_highlevel, host, sizeof(*hi));
	if (hi == NULL) {
		ETH1394_PRINT_G(KERN_ERR, "Out of memory\n");
		goto out;
	}

	ether1394_reset_priv(dev, 1);

	if (register_netdev(dev)) {
		ETH1394_PRINT_G(KERN_ERR, "Cannot register the driver\n");
		goto out;
	}

	ETH1394_PRINT(KERN_INFO, dev->name, "IPv4 over IEEE 1394 (fw-host%d)\n",
		      host->id);

	hi->host = host;
	hi->dev = dev;

	/* Ignore validity in hopes that it will be set in the future.  It'll
	 * be checked when the eth device is opened. */
	priv->broadcast_channel = host->csr.broadcast_channel & 0x3f;

	ether1394_recv_init(priv);
	return;
out:
	if (dev)
		free_netdev(dev);
	if (hi)
		hpsb_destroy_hostinfo(&eth1394_highlevel, host);
	hpsb_unregister_addrspace(&eth1394_highlevel, host, fifo_addr);
	hpsb_config_rom_ip1394_remove(host);
}