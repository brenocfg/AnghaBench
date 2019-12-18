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
struct pcmcia_device {scalar_t__ open; struct net_device* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX88190_init (struct net_device*,int) ; 
 int /*<<< orphan*/  axnet_reset_8390 (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 

__attribute__((used)) static int axnet_resume(struct pcmcia_device *link)
{
	struct net_device *dev = link->priv;

	if (link->open) {
		axnet_reset_8390(dev);
		AX88190_init(dev, 1);
		netif_device_attach(dev);
	}

	return 0;
}