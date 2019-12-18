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
struct ipoib_dev_priv {int /*<<< orphan*/  pkey_poll_task; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int /*<<< orphan*/  IPOIB_PKEY_STOP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_pkey_dev_check_presence (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pkey_mutex ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ipoib_pkey_dev_delay_open(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);

	/* Look for the interface pkey value in the IB Port P_Key table and */
	/* set the interface pkey assigment flag                            */
	ipoib_pkey_dev_check_presence(dev);

	/* P_Key value not assigned yet - start polling */
	if (!test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags)) {
		mutex_lock(&pkey_mutex);
		clear_bit(IPOIB_PKEY_STOP, &priv->flags);
		queue_delayed_work(ipoib_workqueue,
				   &priv->pkey_poll_task,
				   HZ);
		mutex_unlock(&pkey_mutex);
		return 1;
	}

	return 0;
}