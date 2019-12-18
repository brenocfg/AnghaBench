#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; int /*<<< orphan*/ * ml_priv; int /*<<< orphan*/  name; } ;
struct claw_privbk {TYPE_2__* p_env; TYPE_1__* channel; } ;
struct ccwgroup_device {int /*<<< orphan*/ * cdev; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ndev; } ;
struct TYPE_3__ {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int IFF_RUNNING ; 
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  ccw_device_set_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  claw_free_netdevice (struct net_device*,int) ; 
 int claw_release (struct net_device*) ; 
 struct claw_privbk* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int
claw_shutdown_device(struct ccwgroup_device *cgdev)
{
	struct claw_privbk *priv;
	struct net_device *ndev;
	int	ret;

	CLAW_DBF_TEXT_(2, setup, "%s", dev_name(&cgdev->dev));
	priv = dev_get_drvdata(&cgdev->dev);
	if (!priv)
		return -ENODEV;
	ndev = priv->channel[READ].ndev;
	if (ndev) {
		/* Close the device */
		dev_info(&cgdev->dev, "%s: shutting down \n",
			ndev->name);
		if (ndev->flags & IFF_RUNNING)
			ret = claw_release(ndev);
		ndev->flags &=~IFF_RUNNING;
		unregister_netdev(ndev);
		ndev->ml_priv = NULL;  /* cgdev data, not ndev's to free */
		claw_free_netdevice(ndev, 1);
		priv->channel[READ].ndev = NULL;
		priv->channel[WRITE].ndev = NULL;
		priv->p_env->ndev = NULL;
	}
	ccw_device_set_offline(cgdev->cdev[1]);
	ccw_device_set_offline(cgdev->cdev[0]);
	return 0;
}