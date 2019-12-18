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
struct ipoib_dev_priv {int /*<<< orphan*/  napi; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

void ipoib_ib_completion(struct ib_cq *cq, void *dev_ptr)
{
	struct net_device *dev = dev_ptr;
	struct ipoib_dev_priv *priv = netdev_priv(dev);

	napi_schedule(&priv->napi);
}