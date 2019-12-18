#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpfe_device {size_t std_index; int initialized; int /*<<< orphan*/  pdev; int /*<<< orphan*/  v4l2_dev; scalar_t__ current_input; } ;
struct TYPE_4__ {int (* open ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ hw_ops; int /*<<< orphan*/  owner; } ;
struct TYPE_5__ {int /*<<< orphan*/  std_id; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_3__* ccdc_dev ; 
 int /*<<< orphan*/  ccdc_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int vpfe_config_image_format (struct vpfe_device*,int /*<<< orphan*/ *) ; 
 TYPE_2__* vpfe_standards ; 

__attribute__((used)) static int vpfe_initialize_device(struct vpfe_device *vpfe_dev)
{
	int ret = 0;

	/* set first input of current subdevice as the current input */
	vpfe_dev->current_input = 0;

	/* set default standard */
	vpfe_dev->std_index = 0;

	/* Configure the default format information */
	ret = vpfe_config_image_format(vpfe_dev,
				&vpfe_standards[vpfe_dev->std_index].std_id);
	if (ret)
		return ret;

	/* now open the ccdc device to initialize it */
	mutex_lock(&ccdc_lock);
	if (NULL == ccdc_dev) {
		v4l2_err(&vpfe_dev->v4l2_dev, "ccdc device not registered\n");
		ret = -ENODEV;
		goto unlock;
	}

	if (!try_module_get(ccdc_dev->owner)) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Couldn't lock ccdc module\n");
		ret = -ENODEV;
		goto unlock;
	}
	ret = ccdc_dev->hw_ops.open(vpfe_dev->pdev);
	if (!ret)
		vpfe_dev->initialized = 1;
unlock:
	mutex_unlock(&ccdc_lock);
	return ret;
}