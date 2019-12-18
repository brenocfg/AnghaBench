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
struct vmlogrdr_priv_t {int /*<<< orphan*/  priv_lock; scalar_t__ dev_in_use; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct vmlogrdr_priv_t* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vmlogrdr_pm_prepare(struct device *dev)
{
	int rc;
	struct vmlogrdr_priv_t *priv = dev_get_drvdata(dev);

	rc = 0;
	if (priv) {
		spin_lock_bh(&priv->priv_lock);
		if (priv->dev_in_use)
			rc = -EBUSY;
		spin_unlock_bh(&priv->priv_lock);
	}
	if (rc)
		pr_err("vmlogrdr: device %s is busy. Refuse to suspend.\n",
		       dev_name(dev));
	return rc;
}