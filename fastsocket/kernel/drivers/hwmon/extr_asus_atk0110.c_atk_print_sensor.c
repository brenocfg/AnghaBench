#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_5__ {int /*<<< orphan*/  pointer; } ;
union acpi_object {TYPE_3__ integer; TYPE_2__ string; } ;
struct device {int dummy; } ;
struct atk_data {TYPE_1__* acpi_dev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWMON_PACK_ENABLE ; 
 int /*<<< orphan*/  HWMON_PACK_FLAGS ; 
 int /*<<< orphan*/  HWMON_PACK_LIMIT1 ; 
 int /*<<< orphan*/  HWMON_PACK_LIMIT2 ; 
 int /*<<< orphan*/  HWMON_PACK_NAME ; 
 union acpi_object* atk_get_pack_member (struct atk_data*,union acpi_object*,int /*<<< orphan*/ ) ; 
 char* atk_sensor_type (union acpi_object*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*) ; 

__attribute__((used)) static void atk_print_sensor(struct atk_data *data, union acpi_object *obj)
{
#ifdef DEBUG
	struct device *dev = &data->acpi_dev->dev;
	union acpi_object *flags;
	union acpi_object *name;
	union acpi_object *limit1;
	union acpi_object *limit2;
	union acpi_object *enable;
	char const *what;

	flags = atk_get_pack_member(data, obj, HWMON_PACK_FLAGS);
	name = atk_get_pack_member(data, obj, HWMON_PACK_NAME);
	limit1 = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT1);
	limit2 = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT2);
	enable = atk_get_pack_member(data, obj, HWMON_PACK_ENABLE);

	what = atk_sensor_type(flags);

	dev_dbg(dev, "%s: %#llx %s [%llu-%llu] %s\n", what,
			flags->integer.value,
			name->string.pointer,
			limit1->integer.value, limit2->integer.value,
			enable->integer.value ? "enabled" : "disabled");
#endif
}