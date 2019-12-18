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
struct device {int dummy; } ;
struct usb_interface {struct device dev; } ;
struct usb_device_id {int dummy; } ;
struct net_device {int dummy; } ;
struct i1480u {struct net_device* net_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int i1480u_add (struct i1480u*,struct usb_interface*) ; 
 int /*<<< orphan*/  i1480u_netdev_setup ; 
 int /*<<< orphan*/  i1480u_rm (struct i1480u*) ; 
 int /*<<< orphan*/  i1480u_sysfs_setup (struct i1480u*) ; 
 struct i1480u* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int i1480u_probe(struct usb_interface *iface,
			const struct usb_device_id *id)
{
	int result;
	struct net_device *net_dev;
	struct device *dev = &iface->dev;
	struct i1480u *i1480u;

	/* Allocate instance [calls i1480u_netdev_setup() on it] */
	result = -ENOMEM;
	net_dev = alloc_netdev(sizeof(*i1480u), "wlp%d", i1480u_netdev_setup);
	if (net_dev == NULL) {
		dev_err(dev, "no memory for network device instance\n");
		goto error_alloc_netdev;
	}
	SET_NETDEV_DEV(net_dev, dev);
	i1480u = netdev_priv(net_dev);
	i1480u->net_dev = net_dev;
	result = i1480u_add(i1480u, iface);	/* Now setup all the wlp stuff */
	if (result < 0) {
		dev_err(dev, "cannot add i1480u device: %d\n", result);
		goto error_i1480u_add;
	}
	result = register_netdev(net_dev);	/* Okey dokey, bring it up */
	if (result < 0) {
		dev_err(dev, "cannot register network device: %d\n", result);
		goto error_register_netdev;
	}
	i1480u_sysfs_setup(i1480u);
	if (result < 0)
		goto error_sysfs_init;
	return 0;

error_sysfs_init:
	unregister_netdev(net_dev);
error_register_netdev:
	i1480u_rm(i1480u);
error_i1480u_add:
	free_netdev(net_dev);
error_alloc_netdev:
	return result;
}