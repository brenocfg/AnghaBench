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
struct acpi_video_bus {struct acpi_video_bus* attached_array; int /*<<< orphan*/  input; int /*<<< orphan*/  pm_nb; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpi_video_bus* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_video_bus_put_devices (struct acpi_video_bus*) ; 
 int /*<<< orphan*/  acpi_video_bus_remove_fs (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_video_bus_stop_devices (struct acpi_video_bus*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_video_bus*) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_video_bus_remove(struct acpi_device *device, int type)
{
	struct acpi_video_bus *video = NULL;


	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	video = acpi_driver_data(device);

	unregister_pm_notifier(&video->pm_nb);

	acpi_video_bus_stop_devices(video);
	acpi_video_bus_put_devices(video);
	acpi_video_bus_remove_fs(device);

	input_unregister_device(video->input);
	kfree(video->attached_array);
	kfree(video);

	return 0;
}