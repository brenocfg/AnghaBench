#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ command; int /*<<< orphan*/  status; } ;
struct i596_private {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 struct i596_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
i596_timeout(struct net_device *dev, char *msg, int ct) {
	struct i596_private *lp;
	int boguscnt = ct;

	lp = netdev_priv(dev);
	while (lp->scb.command) {
		if (--boguscnt == 0) {
			printk("%s: %s timed out - stat %4.4x, cmd %4.4x\n",
			       dev->name, msg,
			       lp->scb.status, lp->scb.command);
			return 1;
		}
		udelay(5);
		barrier();
	}
	return 0;
}