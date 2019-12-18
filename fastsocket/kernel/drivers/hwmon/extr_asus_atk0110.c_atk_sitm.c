#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; int /*<<< orphan*/ * pointer; } ;
union acpi_object {TYPE_2__ buffer; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct atk_data {int /*<<< orphan*/  write_handle; TYPE_1__* acpi_dev; } ;
struct atk_acpi_input_buf {int /*<<< orphan*/  id; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/  length; } ;
typedef  scalar_t__ acpi_status ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  EIO ; 
 union acpi_object* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_evaluate_object_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_object_list*,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_format_exception (scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,...) ; 

__attribute__((used)) static union acpi_object *atk_sitm(struct atk_data *data,
		struct atk_acpi_input_buf *buf)
{
	struct device *dev = &data->acpi_dev->dev;
	struct acpi_object_list params;
	union acpi_object tmp;
	struct acpi_buffer ret;
	union acpi_object *obj;
	acpi_status status;

	tmp.type = ACPI_TYPE_BUFFER;
	tmp.buffer.pointer = (u8 *)buf;
	tmp.buffer.length = sizeof(*buf);

	params.count = 1;
	params.pointer = &tmp;

	ret.length = ACPI_ALLOCATE_BUFFER;
	status = acpi_evaluate_object_typed(data->write_handle, NULL, &params,
			&ret, ACPI_TYPE_BUFFER);
	if (status != AE_OK) {
		dev_warn(dev, "SITM[%#x] ACPI exception: %s\n", buf->id,
				acpi_format_exception(status));
		return ERR_PTR(-EIO);
	}
	obj = ret.pointer;

	/* Sanity check */
	if (obj->buffer.length < 8) {
		dev_warn(dev, "Unexpected ASBF length: %u\n",
				obj->buffer.length);
		ACPI_FREE(obj);
		return ERR_PTR(-EIO);
	}
	return obj;
}