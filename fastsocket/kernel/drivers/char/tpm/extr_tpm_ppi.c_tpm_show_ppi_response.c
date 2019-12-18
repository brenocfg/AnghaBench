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
struct TYPE_4__ {int value; } ;
struct TYPE_3__ {union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ package; } ;
typedef  int u64 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TPM_PPI_FN_GETRSP ; 
 int /*<<< orphan*/  acpi_evaluate_object_typed (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  ppi_assign_params (union acpi_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppi_callback ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  tpm_device_name ; 

__attribute__((used)) static ssize_t tpm_show_ppi_response(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	acpi_handle handle;
	acpi_status status;
	struct acpi_object_list input;
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object params[4];
	union acpi_object *ret_obj;
	u64 req;

	input.count = 4;
	ppi_assign_params(params, TPM_PPI_FN_GETRSP);
	input.pointer = params;
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				     ACPI_UINT32_MAX, ppi_callback,
				     tpm_device_name, &handle);
	if (ACPI_FAILURE(status))
		return -ENXIO;

	status = acpi_evaluate_object_typed(handle, "_DSM", &input, &output,
					    ACPI_TYPE_PACKAGE);
	if (ACPI_FAILURE(status))
		return -ENOMEM;
	/*
	 * parameter output.pointer should be of package type, including
	 * 3 integers. The first means function return code, the second means
	 * most recent TPM operation request, and the last means response to
	 * the most recent TPM operation request. Only if the first is 0, and
	 * the second integer is not 0, the response makes sense.
	 */
	ret_obj = ((union acpi_object *)output.pointer)->package.elements;
	if (ret_obj->type != ACPI_TYPE_INTEGER) {
		status = -EINVAL;
		goto cleanup;
	}
	if (ret_obj->integer.value) {
		status = -EFAULT;
		goto cleanup;
	}
	ret_obj++;
	if (ret_obj->type != ACPI_TYPE_INTEGER) {
		status = -EINVAL;
		goto cleanup;
	}
	if (ret_obj->integer.value) {
		req = ret_obj->integer.value;
		ret_obj++;
		if (ret_obj->type != ACPI_TYPE_INTEGER) {
			status = -EINVAL;
			goto cleanup;
		}
		if (ret_obj->integer.value == 0)
			status = scnprintf(buf, PAGE_SIZE, "%llu %s\n", req,
					   "0: Success");
		else if (ret_obj->integer.value == 0xFFFFFFF0)
			status = scnprintf(buf, PAGE_SIZE, "%llu %s\n", req,
					   "0xFFFFFFF0: User Abort");
		else if (ret_obj->integer.value == 0xFFFFFFF1)
			status = scnprintf(buf, PAGE_SIZE, "%llu %s\n", req,
					   "0xFFFFFFF1: BIOS Failure");
		else if (ret_obj->integer.value >= 1 &&
			 ret_obj->integer.value <= 0x00000FFF)
			status = scnprintf(buf, PAGE_SIZE, "%llu %llu: %s\n",
					   req, ret_obj->integer.value,
					   "Corresponding TPM error");
		else
			status = scnprintf(buf, PAGE_SIZE, "%llu %llu: %s\n",
					   req, ret_obj->integer.value,
					   "Error");
	} else {
		status = scnprintf(buf, PAGE_SIZE, "%llu: %s\n",
				   ret_obj->integer.value, "No Recent Request");
	}
cleanup:
	kfree(output.pointer);
	return status;
}