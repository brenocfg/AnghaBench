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
struct gem {int opened; int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  asleep; } ;

/* Variables and functions */
 int gem_do_start (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gem* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gem_open(struct net_device *dev)
{
	struct gem *gp = netdev_priv(dev);
	int rc = 0;

	mutex_lock(&gp->pm_mutex);

	/* We need the cell enabled */
	if (!gp->asleep)
		rc = gem_do_start(dev);
	gp->opened = (rc == 0);

	mutex_unlock(&gp->pm_mutex);

	return rc;
}