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
struct node_probe_parameter {int generation; int probe_now; struct hpsb_host* host; } ;
struct hpsb_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_DEBUG (char*) ; 
 scalar_t__ bus_rescan_devices (int /*<<< orphan*/ *) ; 
 scalar_t__ class_for_each_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct node_probe_parameter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee1394_bus_type ; 
 int /*<<< orphan*/  node_probe ; 
 int /*<<< orphan*/  nodemgr_ne_class ; 

__attribute__((used)) static int nodemgr_node_probe(struct hpsb_host *host, int generation)
{
	struct node_probe_parameter p;

	p.host = host;
	p.generation = generation;
	/*
	 * Do some processing of the nodes we've probed. This pulls them
	 * into the sysfs layer if needed, and can result in processing of
	 * unit-directories, or just updating the node and it's
	 * unit-directories.
	 *
	 * Run updates before probes. Usually, updates are time-critical
	 * while probes are time-consuming.
	 *
	 * Meanwhile, another bus reset may have happened. In this case we
	 * skip everything here and let the next bus scan handle it.
	 * Otherwise we may prematurely remove nodes which are still there.
	 */
	p.probe_now = false;
	if (class_for_each_device(&nodemgr_ne_class, NULL, &p, node_probe) != 0)
		return 0;

	p.probe_now = true;
	if (class_for_each_device(&nodemgr_ne_class, NULL, &p, node_probe) != 0)
		return 0;
	/*
	 * Now let's tell the bus to rescan our devices. This may seem
	 * like overhead, but the driver-model core will only scan a
	 * device for a driver when either the device is added, or when a
	 * new driver is added. A bus reset is a good reason to rescan
	 * devices that were there before.  For example, an sbp2 device
	 * may become available for login, if the host that held it was
	 * just removed.
	 */
	if (bus_rescan_devices(&ieee1394_bus_type) != 0)
		HPSB_DEBUG("bus_rescan_devices had an error");

	return 1;
}