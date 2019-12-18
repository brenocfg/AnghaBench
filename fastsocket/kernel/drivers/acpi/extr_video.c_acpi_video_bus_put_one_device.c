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
struct acpi_video_device {int /*<<< orphan*/  output_dev; TYPE_4__* cooling_dev; TYPE_6__* dev; TYPE_5__* backlight; struct acpi_video_bus* video; } ;
struct acpi_video_bus {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_12__ {TYPE_2__ dev; int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_11__ {TYPE_1__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_10__ {TYPE_3__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int ENOENT ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_video_device_notify ; 
 int /*<<< orphan*/  acpi_video_device_remove_fs (TYPE_6__*) ; 
 int /*<<< orphan*/  backlight_device_unregister (TYPE_5__*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (TYPE_4__*) ; 
 int /*<<< orphan*/  video_output_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_video_bus_put_one_device(struct acpi_video_device *device)
{
	acpi_status status;
	struct acpi_video_bus *video;


	if (!device || !device->video)
		return -ENOENT;

	video = device->video;

	acpi_video_device_remove_fs(device->dev);

	status = acpi_remove_notify_handler(device->dev->handle,
					    ACPI_DEVICE_NOTIFY,
					    acpi_video_device_notify);
	if (device->backlight) {
		sysfs_remove_link(&device->backlight->dev.kobj, "device");
		backlight_device_unregister(device->backlight);
		device->backlight = NULL;
	}
	if (device->cooling_dev) {
		sysfs_remove_link(&device->dev->dev.kobj,
				  "thermal_cooling");
		sysfs_remove_link(&device->cooling_dev->device.kobj,
				  "device");
		thermal_cooling_device_unregister(device->cooling_dev);
		device->cooling_dev = NULL;
	}
	video_output_unregister(device->output_dev);

	return 0;
}