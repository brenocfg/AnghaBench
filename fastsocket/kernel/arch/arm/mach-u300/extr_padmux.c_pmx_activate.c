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
struct pmx {int activated; int /*<<< orphan*/  setting; TYPE_1__* onmask; int /*<<< orphan*/ * dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct pmx**) ; 
 int EINVAL ; 
 int EUSERS ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmx_mutex ; 
 struct pmx** pmx_registers ; 
 struct pmx** pmx_settings ; 
 int /*<<< orphan*/  update_registers (struct pmx*,int) ; 

int pmx_activate(struct device *dev, struct pmx *pmx)
{
	int i, j, ret;
	ret = 0;

	if (pmx == NULL || dev == NULL)
		return -EINVAL;

	mutex_lock(&pmx_mutex);

	/* Make sure the required bits are not used */
	for (i = 0; i < ARRAY_SIZE(pmx_settings); i++) {

		if (pmx_settings[i]->dev == NULL || pmx_settings[i] == pmx)
			continue;

		for (j = 0; j < ARRAY_SIZE(pmx_registers); j++) {

			if (pmx_settings[i]->onmask[j].mask & pmx->
				onmask[j].mask) {
				/* More than one entry on the same bits */
				WARN(1, "padmux: cannot activate "
					"setting. Bit conflict with "
					"an active setting\n");

				ret = -EUSERS;
				goto exit;
			}
		}
	}
	update_registers(pmx, true);
	pmx->activated = true;
	dev_dbg(dev, "padmux: setting nr %d is activated\n",
		pmx->setting);

exit:
	mutex_unlock(&pmx_mutex);
	return ret;
}