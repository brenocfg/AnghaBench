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
struct net_device {int flags; struct claw_privbk* ml_priv; int /*<<< orphan*/  name; } ;
struct claw_privbk {TYPE_1__* channel; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int IFF_RUNNING ; 
 size_t READ ; 
 int /*<<< orphan*/  claw_release (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static void
claw_free_netdevice(struct net_device * dev, int free_dev)
{
	struct claw_privbk *privptr;

	CLAW_DBF_TEXT(2, setup, "free_dev");
	if (!dev)
		return;
	CLAW_DBF_TEXT_(2, setup, "%s", dev->name);
	privptr = dev->ml_priv;
	if (dev->flags & IFF_RUNNING)
		claw_release(dev);
	if (privptr) {
		privptr->channel[READ].ndev = NULL;  /* say it's free */
	}
	dev->ml_priv = NULL;
#ifdef MODULE
	if (free_dev) {
		free_netdev(dev);
	}
#endif
	CLAW_DBF_TEXT(2, setup, "free_ok");
}