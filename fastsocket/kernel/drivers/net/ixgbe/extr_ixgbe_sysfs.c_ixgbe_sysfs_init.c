#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* sensor; } ;
struct TYPE_7__ {scalar_t__ (* init_thermal_sensor_thresh ) (TYPE_6__*) ;} ;
struct TYPE_11__ {TYPE_4__ thermal_sensor_data; TYPE_1__ ops; } ;
struct TYPE_12__ {TYPE_5__ mac; } ;
struct hwmon_buff {int /*<<< orphan*/  device; int /*<<< orphan*/  hwmon_list; } ;
struct ixgbe_adapter {TYPE_6__ hw; TYPE_2__* pdev; struct hwmon_buff ixgbe_hwmon_buff; } ;
struct hwmon_attr {int dummy; } ;
struct TYPE_9__ {scalar_t__ location; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_HWMON_TYPE_CAUTION ; 
 int /*<<< orphan*/  IXGBE_HWMON_TYPE_LOC ; 
 int /*<<< orphan*/  IXGBE_HWMON_TYPE_MAX ; 
 int /*<<< orphan*/  IXGBE_HWMON_TYPE_TEMP ; 
 int IXGBE_MAX_SENSORS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (int /*<<< orphan*/ *) ; 
 int ixgbe_add_hwmon_attr (struct ixgbe_adapter*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_sysfs_del_adapter (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_6__*) ; 

int ixgbe_sysfs_init(struct ixgbe_adapter *adapter)
{
	struct hwmon_buff *ixgbe_hwmon = &adapter->ixgbe_hwmon_buff;
	unsigned int i;
	int n_attrs;
	int rc = 0;

	/* If this method isn't defined we don't support thermals */
	if (adapter->hw.mac.ops.init_thermal_sensor_thresh == NULL) {
		goto exit;
	}

	/* Don't create thermal hwmon interface if no sensors present */
	if (adapter->hw.mac.ops.init_thermal_sensor_thresh(&adapter->hw))
		goto exit;

	/*
	 * Allocation space for max attributs
	 * max num sensors * values (loc, temp, max, caution)
	 */
	n_attrs = IXGBE_MAX_SENSORS * 4;
	ixgbe_hwmon->hwmon_list = kcalloc(n_attrs, sizeof(struct hwmon_attr),
					  GFP_KERNEL);
	if (!ixgbe_hwmon->hwmon_list) {
		rc = -ENOMEM;
		goto err;
	}

	ixgbe_hwmon->device = hwmon_device_register(&adapter->pdev->dev);
	if (IS_ERR(ixgbe_hwmon->device)) {
		rc = PTR_ERR(ixgbe_hwmon->device);
		goto err;
	}

	for (i = 0; i < IXGBE_MAX_SENSORS; i++) {
		/*
		 * Only create hwmon sysfs entries for sensors that have
		 * meaningful data for.
		 */
		if (adapter->hw.mac.thermal_sensor_data.sensor[i].location == 0)
			continue;

		/* Bail if any hwmon attr struct fails to initialize */
		rc = ixgbe_add_hwmon_attr(adapter, i, IXGBE_HWMON_TYPE_CAUTION);
		rc |= ixgbe_add_hwmon_attr(adapter, i, IXGBE_HWMON_TYPE_LOC);
		rc |= ixgbe_add_hwmon_attr(adapter, i, IXGBE_HWMON_TYPE_TEMP);
		rc |= ixgbe_add_hwmon_attr(adapter, i, IXGBE_HWMON_TYPE_MAX);
		if (rc)
			goto err;
	}

	goto exit;

err:
	ixgbe_sysfs_del_adapter(adapter);
exit:
	return rc;
}