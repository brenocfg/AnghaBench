#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int n_hwmon; struct hwmon_attr* hwmon_list; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sensor; } ;
struct TYPE_9__ {TYPE_1__ thermal_sensor_data; } ;
struct TYPE_10__ {TYPE_2__ mac; } ;
struct ixgbe_adapter {TYPE_6__ ixgbe_hwmon_buff; TYPE_5__* pdev; TYPE_3__ hw; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; int /*<<< orphan*/  mode; } ;
struct TYPE_14__ {TYPE_4__ attr; int /*<<< orphan*/ * store; int /*<<< orphan*/  show; } ;
struct hwmon_attr {TYPE_7__ dev_attr; int /*<<< orphan*/  name; TYPE_3__* hw; int /*<<< orphan*/ * sensor; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPERM ; 
#define  IXGBE_HWMON_TYPE_CAUTION 131 
#define  IXGBE_HWMON_TYPE_LOC 130 
#define  IXGBE_HWMON_TYPE_MAX 129 
#define  IXGBE_HWMON_TYPE_TEMP 128 
 int /*<<< orphan*/  S_IRUGO ; 
 int device_create_file (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  ixgbe_hwmon_show_cautionthresh ; 
 int /*<<< orphan*/  ixgbe_hwmon_show_location ; 
 int /*<<< orphan*/  ixgbe_hwmon_show_maxopthresh ; 
 int /*<<< orphan*/  ixgbe_hwmon_show_temp ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int) ; 

__attribute__((used)) static int ixgbe_add_hwmon_attr(struct ixgbe_adapter *adapter,
				unsigned int offset, int type) {
	int rc;
	unsigned int n_attr;
	struct hwmon_attr *ixgbe_attr;

	n_attr = adapter->ixgbe_hwmon_buff.n_hwmon;
	ixgbe_attr = &adapter->ixgbe_hwmon_buff.hwmon_list[n_attr];

	switch (type) {
	case IXGBE_HWMON_TYPE_LOC:
		ixgbe_attr->dev_attr.show = ixgbe_hwmon_show_location;
		snprintf(ixgbe_attr->name, sizeof(ixgbe_attr->name),
			 "temp%u_label", offset);
		break;
	case IXGBE_HWMON_TYPE_TEMP:
		ixgbe_attr->dev_attr.show = ixgbe_hwmon_show_temp;
		snprintf(ixgbe_attr->name, sizeof(ixgbe_attr->name),
			 "temp%u_input", offset);
		break;
	case IXGBE_HWMON_TYPE_CAUTION:
		ixgbe_attr->dev_attr.show = ixgbe_hwmon_show_cautionthresh;
		snprintf(ixgbe_attr->name, sizeof(ixgbe_attr->name),
			 "temp%u_max", offset);
		break;
	case IXGBE_HWMON_TYPE_MAX:
		ixgbe_attr->dev_attr.show = ixgbe_hwmon_show_maxopthresh;
		snprintf(ixgbe_attr->name, sizeof(ixgbe_attr->name),
			 "temp%u_crit", offset);
		break;
	default:
		rc = -EPERM;
		return rc;
	}

	/* These always the same regardless of type */
	ixgbe_attr->sensor =
		&adapter->hw.mac.thermal_sensor_data.sensor[offset];
	ixgbe_attr->hw = &adapter->hw;
	ixgbe_attr->dev_attr.store = NULL;
	ixgbe_attr->dev_attr.attr.mode = S_IRUGO;
	ixgbe_attr->dev_attr.attr.name = ixgbe_attr->name;

	rc = device_create_file(&adapter->pdev->dev,
				&ixgbe_attr->dev_attr);

	if (rc == 0)
		++adapter->ixgbe_hwmon_buff.n_hwmon;

	return rc;
}