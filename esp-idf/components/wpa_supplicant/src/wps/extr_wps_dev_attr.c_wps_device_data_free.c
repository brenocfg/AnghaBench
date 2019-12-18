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
struct wps_device_data {int /*<<< orphan*/ * serial_number; int /*<<< orphan*/ * model_number; int /*<<< orphan*/ * model_name; int /*<<< orphan*/ * manufacturer; int /*<<< orphan*/ * device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

void wps_device_data_free(struct wps_device_data *dev)
{
	os_free(dev->device_name);
	dev->device_name = NULL;
	os_free(dev->manufacturer);
	dev->manufacturer = NULL;
	os_free(dev->model_name);
	dev->model_name = NULL;
	os_free(dev->model_number);
	dev->model_number = NULL;
	os_free(dev->serial_number);
	dev->serial_number = NULL;
}