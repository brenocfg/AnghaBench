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
struct net_device {char* name; } ;
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  pc300dev_t ;
struct TYPE_2__ {scalar_t__ priv; } ;

/* Variables and functions */
 int cpc_opench (int /*<<< orphan*/ *) ; 
 TYPE_1__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_close (struct net_device*) ; 
 int hdlc_open (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

int cpc_open(struct net_device *dev)
{
	pc300dev_t *d = (pc300dev_t *) dev_to_hdlc(dev)->priv;
	struct ifreq ifr;
	int result;

#ifdef	PC300_DEBUG_OTHER
	printk("pc300: cpc_open");
#endif

	result = hdlc_open(dev);

	if (result)
		return result;

	sprintf(ifr.ifr_name, "%s", dev->name);
	result = cpc_opench(d);
	if (result)
		goto err_out;

	netif_start_queue(dev);
	return 0;

err_out:
	hdlc_close(dev);
	return result;
}