#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  parent; int /*<<< orphan*/ * type; TYPE_1__* bus; } ;
struct i2c_adapter {scalar_t__ timeout; scalar_t__ nr; TYPE_2__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  bus_lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __i2c_first_dynamic_bus_num ; 
 int bus_for_each_drv (TYPE_1__*,int /*<<< orphan*/ *,struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int class_compat_create_link (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_lock ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_adapter_compat_class ; 
 int /*<<< orphan*/  i2c_adapter_idr ; 
 int /*<<< orphan*/  i2c_adapter_type ; 
 TYPE_1__ i2c_bus_type ; 
 int /*<<< orphan*/  i2c_do_add_adapter ; 
 int /*<<< orphan*/  i2c_scan_static_board_info (struct i2c_adapter*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_register_adapter(struct i2c_adapter *adap)
{
	int res = 0, dummy;

	/* Can't register until after driver model init */
	if (unlikely(WARN_ON(!i2c_bus_type.p))) {
		res = -EAGAIN;
		goto out_list;
	}

	mutex_init(&adap->bus_lock);

	/* Set default timeout to 1 second if not already set */
	if (adap->timeout == 0)
		adap->timeout = HZ;

	dev_set_name(&adap->dev, "i2c-%d", adap->nr);
	adap->dev.bus = &i2c_bus_type;
	adap->dev.type = &i2c_adapter_type;
	res = device_register(&adap->dev);
	if (res)
		goto out_list;

	dev_dbg(&adap->dev, "adapter [%s] registered\n", adap->name);

#ifdef CONFIG_I2C_COMPAT
	res = class_compat_create_link(i2c_adapter_compat_class, &adap->dev,
				       adap->dev.parent);
	if (res)
		dev_warn(&adap->dev,
			 "Failed to create compatibility class link\n");
#endif

	/* create pre-declared device nodes */
	if (adap->nr < __i2c_first_dynamic_bus_num)
		i2c_scan_static_board_info(adap);

	/* Notify drivers */
	mutex_lock(&core_lock);
	dummy = bus_for_each_drv(&i2c_bus_type, NULL, adap,
				 i2c_do_add_adapter);
	mutex_unlock(&core_lock);

	return 0;

out_list:
	mutex_lock(&core_lock);
	idr_remove(&i2c_adapter_idr, adap->nr);
	mutex_unlock(&core_lock);
	return res;
}