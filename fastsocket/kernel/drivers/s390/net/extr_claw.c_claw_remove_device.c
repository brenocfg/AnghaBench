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
struct claw_privbk {TYPE_1__* channel; struct claw_privbk* p_env; struct claw_privbk* p_mtc_envelope; } ;
struct ccwgroup_device {scalar_t__ state; int /*<<< orphan*/  dev; TYPE_2__** cdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct claw_privbk* irb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CCWGROUP_ONLINE ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  claw_remove_files (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  claw_shutdown_device (struct ccwgroup_device*) ; 
 struct claw_privbk* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct claw_privbk*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static void
claw_remove_device(struct ccwgroup_device *cgdev)
{
	struct claw_privbk *priv;

	BUG_ON(!cgdev);
	CLAW_DBF_TEXT_(2, setup, "%s", dev_name(&cgdev->dev));
	priv = dev_get_drvdata(&cgdev->dev);
	BUG_ON(!priv);
	dev_info(&cgdev->dev, " will be removed.\n");
	if (cgdev->state == CCWGROUP_ONLINE)
		claw_shutdown_device(cgdev);
	claw_remove_files(&cgdev->dev);
	kfree(priv->p_mtc_envelope);
	priv->p_mtc_envelope=NULL;
	kfree(priv->p_env);
	priv->p_env=NULL;
	kfree(priv->channel[0].irb);
	priv->channel[0].irb=NULL;
	kfree(priv->channel[1].irb);
	priv->channel[1].irb=NULL;
	kfree(priv);
	dev_set_drvdata(&cgdev->dev, NULL);
	dev_set_drvdata(&cgdev->cdev[READ]->dev, NULL);
	dev_set_drvdata(&cgdev->cdev[WRITE]->dev, NULL);
	put_device(&cgdev->dev);

	return;
}