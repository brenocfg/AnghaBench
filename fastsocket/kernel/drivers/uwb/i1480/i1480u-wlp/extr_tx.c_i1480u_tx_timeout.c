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
struct i1480u {int /*<<< orphan*/  wlp; } ;

/* Variables and functions */
 struct i1480u* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wlp_reset_all (int /*<<< orphan*/ *) ; 

void i1480u_tx_timeout(struct net_device *net_dev)
{
	struct i1480u *i1480u = netdev_priv(net_dev);

	wlp_reset_all(&i1480u->wlp);
}