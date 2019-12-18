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
struct rndis_device {int /*<<< orphan*/  hw_mac_adr; scalar_t__ link_state; struct netvsc_device* net_dev; } ;
struct netvsc_device_info {scalar_t__ link_state; int /*<<< orphan*/  mac_adr; } ;
struct netvsc_device {struct rndis_device* extension; } ;
struct hv_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 struct rndis_device* get_rndis_device () ; 
 struct netvsc_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  kfree (struct rndis_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int netvsc_device_add (struct hv_device*,void*) ; 
 int /*<<< orphan*/  rndis_filter_device_remove (struct hv_device*) ; 
 int rndis_filter_init_device (struct rndis_device*) ; 
 int /*<<< orphan*/  rndis_filter_query_device_link_status (struct rndis_device*) ; 
 int rndis_filter_query_device_mac (struct rndis_device*) ; 

int rndis_filter_device_add(struct hv_device *dev,
				  void *additional_info)
{
	int ret;
	struct netvsc_device *net_device;
	struct rndis_device *rndis_device;
	struct netvsc_device_info *device_info = additional_info;

	rndis_device = get_rndis_device();
	if (!rndis_device)
		return -ENODEV;

	/*
	 * Let the inner driver handle this first to create the netvsc channel
	 * NOTE! Once the channel is created, we may get a receive callback
	 * (RndisFilterOnReceive()) before this call is completed
	 */
	ret = netvsc_device_add(dev, additional_info);
	if (ret != 0) {
		kfree(rndis_device);
		return ret;
	}


	/* Initialize the rndis device */
	net_device = hv_get_drvdata(dev);

	net_device->extension = rndis_device;
	rndis_device->net_dev = net_device;

	/* Send the rndis initialization message */
	ret = rndis_filter_init_device(rndis_device);
	if (ret != 0) {
		rndis_filter_device_remove(dev);
		return ret;
	}

	/* Get the mac address */
	ret = rndis_filter_query_device_mac(rndis_device);
	if (ret != 0) {
		rndis_filter_device_remove(dev);
		return ret;
	}

	memcpy(device_info->mac_adr, rndis_device->hw_mac_adr, ETH_ALEN);

	rndis_filter_query_device_link_status(rndis_device);

	device_info->link_state = rndis_device->link_state;

	dev_info(&dev->device, "Device MAC %pM link state %s\n",
		 rndis_device->hw_mac_adr,
		 device_info->link_state ? "down" : "up");

	return ret;
}