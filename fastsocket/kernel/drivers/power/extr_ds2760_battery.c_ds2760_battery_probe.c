#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  external_power_changed; int /*<<< orphan*/  set_charged; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct ds2760_device_info {char* raw; TYPE_1__ bat; int /*<<< orphan*/  monitor_work; int /*<<< orphan*/  monitor_wqueue; int /*<<< orphan*/  set_charged_work; TYPE_2__* dev; int /*<<< orphan*/  charge_status; int /*<<< orphan*/  w1_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 char DS2760_STATUS_PMOD ; 
 size_t DS2760_STATUS_REG ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 scalar_t__ current_accum ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  ds2760_battery_external_power_changed ; 
 int /*<<< orphan*/  ds2760_battery_get_property ; 
 int /*<<< orphan*/  ds2760_battery_props ; 
 int /*<<< orphan*/  ds2760_battery_read_status (struct ds2760_device_info*) ; 
 int /*<<< orphan*/  ds2760_battery_set_charged ; 
 int /*<<< orphan*/  ds2760_battery_set_charged_work ; 
 int /*<<< orphan*/  ds2760_battery_set_current_accum (struct ds2760_device_info*,scalar_t__) ; 
 int /*<<< orphan*/  ds2760_battery_work ; 
 int /*<<< orphan*/  ds2760_battery_write_rated_capacity (struct ds2760_device_info*,scalar_t__) ; 
 int /*<<< orphan*/  ds2760_battery_write_status (struct ds2760_device_info*,char) ; 
 int /*<<< orphan*/  kfree (struct ds2760_device_info*) ; 
 struct ds2760_device_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ds2760_device_info*) ; 
 scalar_t__ pmod_enabled ; 
 int power_supply_register (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  power_supply_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ rated_capacity ; 

__attribute__((used)) static int ds2760_battery_probe(struct platform_device *pdev)
{
	char status;
	int retval = 0;
	struct ds2760_device_info *di;

	di = kzalloc(sizeof(*di), GFP_KERNEL);
	if (!di) {
		retval = -ENOMEM;
		goto di_alloc_failed;
	}

	platform_set_drvdata(pdev, di);

	di->dev			= &pdev->dev;
	di->w1_dev		= pdev->dev.parent;
	di->bat.name		= dev_name(&pdev->dev);
	di->bat.type		= POWER_SUPPLY_TYPE_BATTERY;
	di->bat.properties	= ds2760_battery_props;
	di->bat.num_properties	= ARRAY_SIZE(ds2760_battery_props);
	di->bat.get_property	= ds2760_battery_get_property;
	di->bat.set_charged	= ds2760_battery_set_charged;
	di->bat.external_power_changed =
				  ds2760_battery_external_power_changed;

	di->charge_status = POWER_SUPPLY_STATUS_UNKNOWN;

	/* enable sleep mode feature */
	ds2760_battery_read_status(di);
	status = di->raw[DS2760_STATUS_REG];
	if (pmod_enabled)
		status |= DS2760_STATUS_PMOD;
	else
		status &= ~DS2760_STATUS_PMOD;

	ds2760_battery_write_status(di, status);

	/* set rated capacity from module param */
	if (rated_capacity)
		ds2760_battery_write_rated_capacity(di, rated_capacity);

	/* set current accumulator if given as parameter.
	 * this should only be done for bootstrapping the value */
	if (current_accum)
		ds2760_battery_set_current_accum(di, current_accum);

	retval = power_supply_register(&pdev->dev, &di->bat);
	if (retval) {
		dev_err(di->dev, "failed to register battery\n");
		goto batt_failed;
	}

	INIT_DELAYED_WORK(&di->monitor_work, ds2760_battery_work);
	INIT_DELAYED_WORK(&di->set_charged_work,
			  ds2760_battery_set_charged_work);
	di->monitor_wqueue = create_singlethread_workqueue(dev_name(&pdev->dev));
	if (!di->monitor_wqueue) {
		retval = -ESRCH;
		goto workqueue_failed;
	}
	queue_delayed_work(di->monitor_wqueue, &di->monitor_work, HZ * 1);

	goto success;

workqueue_failed:
	power_supply_unregister(&di->bat);
batt_failed:
	kfree(di);
di_alloc_failed:
success:
	return retval;
}