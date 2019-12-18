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
struct znet_private {scalar_t__ sia_base; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int inb (scalar_t__) ; 
 struct znet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void znet_transceiver_power (struct net_device *dev, int on)
{
	struct znet_private *znet = netdev_priv(dev);
	unsigned char v;

	/* Turn on/off the 82501 SIA, using zenith-specific magic. */
	/* Select LAN control register */
	outb(0x10, znet->sia_base);

	if (on)
		v = inb(znet->sia_base + 1) | 0x84;
	else
		v = inb(znet->sia_base + 1) & ~0x84;

	outb(v, znet->sia_base+1); /* Turn on/off LAN power (bit 2). */
}