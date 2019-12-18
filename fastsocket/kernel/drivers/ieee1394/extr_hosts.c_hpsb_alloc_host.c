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
typedef  int /*<<< orphan*/  u8 ;
struct hpsb_host_driver {int dummy; } ;
struct device {int /*<<< orphan*/ * class; struct device* parent; } ;
struct TYPE_3__ {scalar_t__ speed_map; scalar_t__ topology_map; scalar_t__* gen_timestamp; int /*<<< orphan*/  rom; } ;
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct hpsb_host {int timeout_interval; int id; struct device device; struct device host_dev; TYPE_1__ csr; int /*<<< orphan*/ * speed_map; scalar_t__ topology_map; TYPE_2__ timeout; int /*<<< orphan*/  delayed_reset; int /*<<< orphan*/  generation; int /*<<< orphan*/  addr_space; int /*<<< orphan*/  pending_packets; struct hpsb_host_driver* driver; struct hpsb_host* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_BUS_INFO_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort_timedouts ; 
 int /*<<< orphan*/  alloc_hostnum_cb ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csr1212_create_csr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hpsb_host*) ; 
 int /*<<< orphan*/  csr_bus_ops ; 
 int /*<<< orphan*/  delayed_reset_bus ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_to_node (struct device*) ; 
 scalar_t__ device_register (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  host_num_alloc ; 
 int /*<<< orphan*/  hpsb_host_class ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct hpsb_host*) ; 
 struct hpsb_host* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodemgr_dev_template_host ; 
 scalar_t__ nodemgr_for_each_host (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dev_node (struct device*,int /*<<< orphan*/ ) ; 

struct hpsb_host *hpsb_alloc_host(struct hpsb_host_driver *drv, size_t extra,
				  struct device *dev)
{
	struct hpsb_host *h;
	int i;
	int hostnum = 0;

	h = kzalloc(sizeof(*h) + extra, GFP_KERNEL);
	if (!h)
		return NULL;

	h->csr.rom = csr1212_create_csr(&csr_bus_ops, CSR_BUS_INFO_SIZE, h);
	if (!h->csr.rom)
		goto fail;

	h->hostdata = h + 1;
	h->driver = drv;

	INIT_LIST_HEAD(&h->pending_packets);
	INIT_LIST_HEAD(&h->addr_space);

	for (i = 2; i < 16; i++)
		h->csr.gen_timestamp[i] = jiffies - 60 * HZ;

	atomic_set(&h->generation, 0);

	INIT_DELAYED_WORK(&h->delayed_reset, delayed_reset_bus);
	
	init_timer(&h->timeout);
	h->timeout.data = (unsigned long) h;
	h->timeout.function = abort_timedouts;
	h->timeout_interval = HZ / 20; /* 50ms, half of minimum SPLIT_TIMEOUT */

	h->topology_map = h->csr.topology_map + 3;
	h->speed_map = (u8 *)(h->csr.speed_map + 2);

	mutex_lock(&host_num_alloc);
	while (nodemgr_for_each_host(&hostnum, alloc_hostnum_cb))
		hostnum++;
	mutex_unlock(&host_num_alloc);
	h->id = hostnum;

	memcpy(&h->device, &nodemgr_dev_template_host, sizeof(h->device));
	h->device.parent = dev;
	set_dev_node(&h->device, dev_to_node(dev));
	dev_set_name(&h->device, "fw-host%d", h->id);

	h->host_dev.parent = &h->device;
	h->host_dev.class = &hpsb_host_class;
	dev_set_name(&h->host_dev, "fw-host%d", h->id);

	if (device_register(&h->device))
		goto fail;
	if (device_register(&h->host_dev)) {
		device_unregister(&h->device);
		goto fail;
	}
	get_device(&h->device);

	return h;

fail:
	kfree(h);
	return NULL;
}