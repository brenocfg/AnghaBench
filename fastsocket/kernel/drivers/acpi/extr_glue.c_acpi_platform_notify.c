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
struct TYPE_2__ {int /*<<< orphan*/  acpi_handle; } ;
struct device {TYPE_1__ archdata; int /*<<< orphan*/  bus; int /*<<< orphan*/  parent; } ;
struct acpi_bus_type {int (* find_device ) (struct device*,int /*<<< orphan*/ *) ;} ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_bind_one (struct device*,int /*<<< orphan*/ ) ; 
 int acpi_find_bridge_device (struct device*,int /*<<< orphan*/ *) ; 
 struct acpi_bus_type* acpi_get_bus_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int stub1 (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_platform_notify(struct device *dev)
{
	struct acpi_bus_type *type;
	acpi_handle handle;
	int ret = -EINVAL;

	if (!dev->bus || !dev->parent) {
		/* bridge devices genernally haven't bus or parent */
		ret = acpi_find_bridge_device(dev, &handle);
		goto end;
	}
	type = acpi_get_bus_type(dev->bus);
	if (!type) {
		DBG("No ACPI bus support for %s\n", dev_name(dev));
		ret = -EINVAL;
		goto end;
	}
	if ((ret = type->find_device(dev, &handle)) != 0)
		DBG("Can't get handler for %s\n", dev_name(dev));
      end:
	if (!ret)
		acpi_bind_one(dev, handle);

#if ACPI_GLUE_DEBUG
	if (!ret) {
		struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };

		acpi_get_name(dev->archdata.acpi_handle,
			      ACPI_FULL_PATHNAME, &buffer);
		DBG("Device %s -> %s\n", dev_name(dev), (char *)buffer.pointer);
		kfree(buffer.pointer);
	} else
		DBG("Device %s -> No ACPI support\n", dev_name(dev));
#endif

	return ret;
}