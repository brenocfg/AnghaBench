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
struct net_device {int dummy; } ;
struct fst_port_info {scalar_t__ mode; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ FST_RAW ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct fst_port_info* dev_to_port (struct net_device*) ; 
 int /*<<< orphan*/  fst_openport (struct fst_port_info*) ; 
 int hdlc_open (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fst_open(struct net_device *dev)
{
	int err;
	struct fst_port_info *port;

	port = dev_to_port(dev);
	if (!try_module_get(THIS_MODULE))
          return -EBUSY;

	if (port->mode != FST_RAW) {
		err = hdlc_open(dev);
		if (err)
			return err;
	}

	fst_openport(port);
	netif_wake_queue(dev);
	return 0;
}