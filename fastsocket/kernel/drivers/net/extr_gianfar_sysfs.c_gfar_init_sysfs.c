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
struct net_device {int /*<<< orphan*/  dev; } ;
struct gfar_private {int /*<<< orphan*/  fifo_starve_off; int /*<<< orphan*/  fifo_starve; int /*<<< orphan*/  fifo_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FIFO_TX_STARVE ; 
 int /*<<< orphan*/  DEFAULT_FIFO_TX_STARVE_OFF ; 
 int /*<<< orphan*/  DEFAULT_FIFO_TX_THR ; 
 int /*<<< orphan*/  dev_attr_bd_stash ; 
 int /*<<< orphan*/  dev_attr_fifo_starve ; 
 int /*<<< orphan*/  dev_attr_fifo_starve_off ; 
 int /*<<< orphan*/  dev_attr_fifo_threshold ; 
 int /*<<< orphan*/  dev_attr_rx_stash_index ; 
 int /*<<< orphan*/  dev_attr_rx_stash_size ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 

void gfar_init_sysfs(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	int rc;

	/* Initialize the default values */
	priv->fifo_threshold = DEFAULT_FIFO_TX_THR;
	priv->fifo_starve = DEFAULT_FIFO_TX_STARVE;
	priv->fifo_starve_off = DEFAULT_FIFO_TX_STARVE_OFF;

	/* Create our sysfs files */
	rc = device_create_file(&dev->dev, &dev_attr_bd_stash);
	rc |= device_create_file(&dev->dev, &dev_attr_rx_stash_size);
	rc |= device_create_file(&dev->dev, &dev_attr_rx_stash_index);
	rc |= device_create_file(&dev->dev, &dev_attr_fifo_threshold);
	rc |= device_create_file(&dev->dev, &dev_attr_fifo_starve);
	rc |= device_create_file(&dev->dev, &dev_attr_fifo_starve_off);
	if (rc)
		dev_err(&dev->dev, "Error creating gianfar sysfs files.\n");
}