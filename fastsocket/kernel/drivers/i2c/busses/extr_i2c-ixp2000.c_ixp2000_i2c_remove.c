#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int dummy; } ;
struct ixp2000_i2c_data {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ixp2000_i2c_data*) ; 
 struct ixp2000_i2c_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixp2000_i2c_remove(struct platform_device *plat_dev)
{
	struct ixp2000_i2c_data *drv_data = platform_get_drvdata(plat_dev);

	platform_set_drvdata(plat_dev, NULL);

	i2c_del_adapter(&drv_data->adapter);

	kfree(drv_data);

	return 0;
}