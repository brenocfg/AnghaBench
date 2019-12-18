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
struct regulator_dev {int dummy; } ;
struct lp3971_platform_data {int num_regulators; TYPE_1__* regulators; } ;
struct lp3971 {int num_regulators; scalar_t__* rdev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int id; int /*<<< orphan*/  initdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ regulator_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lp3971*) ; 
 int /*<<< orphan*/  regulator_unregister (scalar_t__) ; 
 int /*<<< orphan*/ * regulators ; 

__attribute__((used)) static int setup_regulators(struct lp3971 *lp3971,
	struct lp3971_platform_data *pdata)
{
	int i, err;
	int num_regulators = pdata->num_regulators;
	lp3971->num_regulators = num_regulators;
	lp3971->rdev = kzalloc(sizeof(struct regulator_dev *) * num_regulators,
		GFP_KERNEL);

	/* Instantiate the regulators */
	for (i = 0; i < num_regulators; i++) {
		int id = pdata->regulators[i].id;
		lp3971->rdev[i] = regulator_register(&regulators[id],
			lp3971->dev, pdata->regulators[i].initdata, lp3971);

		err = IS_ERR(lp3971->rdev[i]);
		if (err) {
			dev_err(lp3971->dev, "regulator init failed: %d\n",
				err);
			goto error;
		}
	}

	return 0;
error:
	for (i = 0; i < num_regulators; i++)
		if (lp3971->rdev[i])
			regulator_unregister(lp3971->rdev[i]);
	kfree(lp3971->rdev);
	lp3971->rdev = NULL;
	return err;
}