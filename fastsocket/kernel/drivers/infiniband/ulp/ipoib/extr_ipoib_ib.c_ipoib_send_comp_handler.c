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
struct ipoib_dev_priv {int /*<<< orphan*/  poll_timer; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* netdev_priv (void*) ; 

void ipoib_send_comp_handler(struct ib_cq *cq, void *dev_ptr)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev_ptr);

	mod_timer(&priv->poll_timer, jiffies);
}