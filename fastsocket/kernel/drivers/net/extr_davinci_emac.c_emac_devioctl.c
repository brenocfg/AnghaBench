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
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int emac_devioctl(struct net_device *ndev, struct ifreq *ifrq, int cmd)
{
	dev_warn(&ndev->dev, "DaVinci EMAC: ioctl not supported\n");

	if (!(netif_running(ndev)))
		return -EINVAL;

	/* TODO: Add phy read and write and private statistics get feature */

	return -EOPNOTSUPP;
}