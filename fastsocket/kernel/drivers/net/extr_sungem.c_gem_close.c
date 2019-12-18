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
struct gem {int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  asleep; scalar_t__ opened; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  gem_do_stop (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct gem* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gem_close(struct net_device *dev)
{
	struct gem *gp = netdev_priv(dev);

	mutex_lock(&gp->pm_mutex);

	napi_disable(&gp->napi);

	gp->opened = 0;
	if (!gp->asleep)
		gem_do_stop(dev, 0);

	mutex_unlock(&gp->pm_mutex);

	return 0;
}