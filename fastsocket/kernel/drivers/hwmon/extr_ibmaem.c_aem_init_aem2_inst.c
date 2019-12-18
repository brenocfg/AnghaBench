#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct aem_ipmi_data {int /*<<< orphan*/  interface; int /*<<< orphan*/  bmc_device; } ;
struct aem_find_instance_resp {int /*<<< orphan*/  module_handle; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_13__ {int /*<<< orphan*/  user; int /*<<< orphan*/  bmc_device; } ;
struct aem_data {int /*<<< orphan*/  id; TYPE_1__* pdev; TYPE_8__ ipmi; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  module_handle; int /*<<< orphan*/  ver_minor; int /*<<< orphan*/  ver_major; int /*<<< orphan*/  list; int /*<<< orphan*/  update; int /*<<< orphan*/ * power_period; int /*<<< orphan*/  lock; } ;
struct TYPE_14__ {int /*<<< orphan*/  driver; } ;
struct TYPE_12__ {int /*<<< orphan*/  aem_devices; } ;
struct TYPE_11__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_10__ {TYPE_4__ dev; } ;

/* Variables and functions */
 int AEM2_NUM_ENERGY_REGS ; 
 int /*<<< orphan*/  AEM_DEFAULT_POWER_INTERVAL ; 
 int /*<<< orphan*/  DRVNAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ aem2_find_sensors (struct aem_data*) ; 
 TYPE_9__ aem_driver ; 
 scalar_t__ aem_idr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aem_idr_put (int /*<<< orphan*/ ) ; 
 scalar_t__ aem_init_ipmi_data (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct aem_data*) ; 
 TYPE_5__ driver_data ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_4__*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aem_data*) ; 
 struct aem_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_device_add (TYPE_1__*) ; 
 TYPE_1__* platform_device_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  update_aem2_sensors ; 

__attribute__((used)) static int aem_init_aem2_inst(struct aem_ipmi_data *probe,
			      struct aem_find_instance_resp *fi_resp)
{
	struct aem_data *data;
	int i;
	int res = -ENOMEM;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return res;
	mutex_init(&data->lock);

	/* Copy instance data */
	data->ver_major = fi_resp->major;
	data->ver_minor = fi_resp->minor;
	data->module_handle = fi_resp->module_handle;
	for (i = 0; i < AEM2_NUM_ENERGY_REGS; i++)
		data->power_period[i] = AEM_DEFAULT_POWER_INTERVAL;

	/* Create sub-device for this fw instance */
	if (aem_idr_get(&data->id))
		goto id_err;

	data->pdev = platform_device_alloc(DRVNAME, data->id);
	if (!data->pdev)
		goto dev_err;
	data->pdev->dev.driver = &aem_driver.driver;

	res = platform_device_add(data->pdev);
	if (res)
		goto ipmi_err;

	dev_set_drvdata(&data->pdev->dev, data);

	/* Set up IPMI interface */
	if (aem_init_ipmi_data(&data->ipmi, probe->interface,
			       probe->bmc_device))
		goto ipmi_err;

	/* Register with hwmon */
	data->hwmon_dev = hwmon_device_register(&data->pdev->dev);

	if (IS_ERR(data->hwmon_dev)) {
		dev_err(&data->pdev->dev, "Unable to register hwmon "
			"device for IPMI interface %d\n",
			probe->interface);
		goto hwmon_reg_err;
	}

	data->update = update_aem2_sensors;

	/* Find sensors */
	if (aem2_find_sensors(data))
		goto sensor_err;

	/* Add to our list of AEM devices */
	list_add_tail(&data->list, &driver_data.aem_devices);

	dev_info(data->ipmi.bmc_device, "Found AEM v%d.%d at 0x%X\n",
		 data->ver_major, data->ver_minor,
		 data->module_handle);
	return 0;

sensor_err:
	hwmon_device_unregister(data->hwmon_dev);
hwmon_reg_err:
	ipmi_destroy_user(data->ipmi.user);
ipmi_err:
	dev_set_drvdata(&data->pdev->dev, NULL);
	platform_device_unregister(data->pdev);
dev_err:
	aem_idr_put(data->id);
id_err:
	kfree(data);

	return res;
}