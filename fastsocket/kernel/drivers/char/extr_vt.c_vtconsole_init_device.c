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
struct con_driver {int /*<<< orphan*/  flag; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CON_DRIVER_FLAG_ATTR ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct con_driver*) ; 
 int /*<<< orphan*/ * device_attrs ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vtconsole_init_device(struct con_driver *con)
{
	int i;
	int error = 0;

	con->flag |= CON_DRIVER_FLAG_ATTR;
	dev_set_drvdata(con->dev, con);
	for (i = 0; i < ARRAY_SIZE(device_attrs); i++) {
		error = device_create_file(con->dev, &device_attrs[i]);
		if (error)
			break;
	}

	if (error) {
		while (--i >= 0)
			device_remove_file(con->dev, &device_attrs[i]);
		con->flag &= ~CON_DRIVER_FLAG_ATTR;
	}

	return error;
}