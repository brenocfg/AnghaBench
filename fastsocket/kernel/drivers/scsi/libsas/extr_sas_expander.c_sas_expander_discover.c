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
struct expander_device {int num_phys; int /*<<< orphan*/ * ex_phy; } ;
struct domain_device {struct expander_device ex_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int sas_ex_phy_discover (struct domain_device*,int) ; 

__attribute__((used)) static int sas_expander_discover(struct domain_device *dev)
{
	struct expander_device *ex = &dev->ex_dev;
	int res = -ENOMEM;

	ex->ex_phy = kzalloc(sizeof(*ex->ex_phy)*ex->num_phys, GFP_KERNEL);
	if (!ex->ex_phy)
		return -ENOMEM;

	res = sas_ex_phy_discover(dev, -1);
	if (res)
		goto out_err;

	return 0;
 out_err:
	kfree(ex->ex_phy);
	ex->ex_phy = NULL;
	return res;
}