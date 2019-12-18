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
struct output_device {unsigned long request_state; int /*<<< orphan*/  dev; } ;
struct acpi_video_device {int dummy; } ;

/* Variables and functions */
 int acpi_video_device_set_state (struct acpi_video_device*,unsigned long) ; 
 scalar_t__ dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_video_output_set(struct output_device *od)
{
	unsigned long state = od->request_state;
	struct acpi_video_device *vd=
		(struct acpi_video_device *)dev_get_drvdata(&od->dev);
	return acpi_video_device_set_state(vd, state);
}