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
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct omap_device {scalar_t__ _state; int /*<<< orphan*/  _dev_wakeup_lat_limit; scalar_t__ dev_wakeup_lat; int /*<<< orphan*/  pm_lats_cnt; int /*<<< orphan*/  pm_lat_level; TYPE_1__ pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IGNORE_WAKEUP_LAT ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ OMAP_DEVICE_STATE_ENABLED ; 
 scalar_t__ OMAP_DEVICE_STATE_UNKNOWN ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_device* _find_by_pdev (struct platform_device*) ; 
 int _omap_device_activate (struct omap_device*,int /*<<< orphan*/ ) ; 

int omap_device_enable(struct platform_device *pdev)
{
	int ret;
	struct omap_device *od;

	od = _find_by_pdev(pdev);

	if (od->_state == OMAP_DEVICE_STATE_ENABLED) {
		WARN(1, "omap_device: %s.%d: omap_device_enable() called from "
		     "invalid state\n", od->pdev.name, od->pdev.id);
		return -EINVAL;
	}

	/* Enable everything if we're enabling this device from scratch */
	if (od->_state == OMAP_DEVICE_STATE_UNKNOWN)
		od->pm_lat_level = od->pm_lats_cnt;

	ret = _omap_device_activate(od, IGNORE_WAKEUP_LAT);

	od->dev_wakeup_lat = 0;
	od->_dev_wakeup_lat_limit = INT_MAX;
	od->_state = OMAP_DEVICE_STATE_ENABLED;

	return ret;
}