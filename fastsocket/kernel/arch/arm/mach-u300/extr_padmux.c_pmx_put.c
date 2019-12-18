#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmx {scalar_t__ setting; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {scalar_t__ setting; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmx_mutex ; 
 TYPE_1__** pmx_settings ; 

int pmx_put(struct device *dev, struct pmx *pmx)
{
	int i;
	int ret = -ENOENT;

	if (pmx == NULL || dev == NULL)
		return -EINVAL;

	mutex_lock(&pmx_mutex);
	for (i = 0; i < ARRAY_SIZE(pmx_settings); i++) {

		if (pmx->setting == pmx_settings[i]->setting) {

			if (dev != pmx->dev) {
				WARN(1, "padmux: cannot release handle as "
					"it is bound to another consumer\n");
				ret = -EINVAL;
				break;
			} else {
				pmx_settings[i]->dev = NULL;
				ret = 0;
				break;
			}
		}
	}
	mutex_unlock(&pmx_mutex);

	return ret;
}