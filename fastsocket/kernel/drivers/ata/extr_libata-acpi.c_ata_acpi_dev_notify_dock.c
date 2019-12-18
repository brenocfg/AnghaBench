#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ata_device {TYPE_1__* link; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_acpi_handle_hotplug (int /*<<< orphan*/ ,struct ata_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ata_acpi_dev_notify_dock(acpi_handle handle, u32 event, void *data)
{
	struct ata_device *dev = data;

	ata_acpi_handle_hotplug(dev->link->ap, dev, event);
}