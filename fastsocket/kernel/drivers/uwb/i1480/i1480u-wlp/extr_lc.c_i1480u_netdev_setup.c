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
struct i1480u {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i1480u_init (struct i1480u*) ; 
 int /*<<< orphan*/  memset (struct i1480u*,int /*<<< orphan*/ ,int) ; 
 struct i1480u* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void i1480u_netdev_setup(struct net_device *net_dev)
{
	struct i1480u *i1480u = netdev_priv(net_dev);
	/* Initialize @i1480u */
	memset(i1480u, 0, sizeof(*i1480u));
	i1480u_init(i1480u);
}