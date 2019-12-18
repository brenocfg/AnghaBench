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
struct platform_device {int dummy; } ;
struct omap_hwmod {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct omap_device {scalar_t__ _state; int hwmods_cnt; struct omap_hwmod** hwmods; TYPE_1__ pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IGNORE_WAKEUP_LAT ; 
 scalar_t__ OMAP_DEVICE_STATE_ENABLED ; 
 scalar_t__ OMAP_DEVICE_STATE_IDLE ; 
 scalar_t__ OMAP_DEVICE_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_device* _find_by_pdev (struct platform_device*) ; 
 int _omap_device_deactivate (struct omap_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hwmod_shutdown (struct omap_hwmod*) ; 

int omap_device_shutdown(struct platform_device *pdev)
{
	int ret, i;
	struct omap_device *od;
	struct omap_hwmod *oh;

	od = _find_by_pdev(pdev);

	if (od->_state != OMAP_DEVICE_STATE_ENABLED &&
	    od->_state != OMAP_DEVICE_STATE_IDLE) {
		WARN(1, "omap_device: %s.%d: omap_device_shutdown() called "
		     "from invalid state\n", od->pdev.name, od->pdev.id);
		return -EINVAL;
	}

	ret = _omap_device_deactivate(od, IGNORE_WAKEUP_LAT);

	for (i = 0, oh = *od->hwmods; i < od->hwmods_cnt; i++, oh++)
		omap_hwmod_shutdown(oh);

	od->_state = OMAP_DEVICE_STATE_SHUTDOWN;

	return ret;
}