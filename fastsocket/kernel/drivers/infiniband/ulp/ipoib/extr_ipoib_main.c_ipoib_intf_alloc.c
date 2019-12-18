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
struct ipoib_dev_priv {int dummy; } ;

/* Variables and functions */
 struct net_device* alloc_netdev (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_setup ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

struct ipoib_dev_priv *ipoib_intf_alloc(const char *name)
{
	struct net_device *dev;

	dev = alloc_netdev((int) sizeof (struct ipoib_dev_priv), name,
			   ipoib_setup);
	if (!dev)
		return NULL;

	return netdev_priv(dev);
}