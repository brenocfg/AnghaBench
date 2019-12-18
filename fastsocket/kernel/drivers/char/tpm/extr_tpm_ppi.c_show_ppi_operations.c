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
struct TYPE_6__ {int value; } ;
struct TYPE_5__ {int count; union acpi_object* elements; } ;
struct TYPE_4__ {int /*<<< orphan*/  pointer; } ;
union acpi_object {TYPE_3__ integer; TYPE_2__ package; int /*<<< orphan*/  type; TYPE_1__ string; } ;
typedef  int u32 ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {void* member_0; int /*<<< orphan*/ * pointer; void* length; int /*<<< orphan*/ * member_1; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 void* ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int ARRAY_SIZE (char**) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PPI_VERSION_LEN ; 
 int TPM_PPI_FN_GETOPR ; 
 int /*<<< orphan*/  TPM_PPI_FN_VERSION ; 
 int /*<<< orphan*/  acpi_evaluate_object_typed (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppi_assign_params (union acpi_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppi_callback ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tpm_device_name ; 

__attribute__((used)) static ssize_t show_ppi_operations(char *buf, u32 start, u32 end)
{
	char *str = buf;
	char version[PPI_VERSION_LEN];
	acpi_handle handle;
	acpi_status status;
	struct acpi_object_list input;
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object params[4];
	union acpi_object obj;
	int i;
	u32 ret;
	char *info[] = {
		"Not implemented",
		"BIOS only",
		"Blocked for OS by BIOS",
		"User required",
		"User not required",
	};
	input.count = 4;
	ppi_assign_params(params, TPM_PPI_FN_VERSION);
	input.pointer = params;
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				     ACPI_UINT32_MAX, ppi_callback,
				     tpm_device_name, &handle);
	if (ACPI_FAILURE(status))
		return -ENXIO;

	status = acpi_evaluate_object_typed(handle, "_DSM", &input, &output,
					 ACPI_TYPE_STRING);
	if (ACPI_FAILURE(status))
		return -ENOMEM;

	strncpy(version,
		((union acpi_object *)output.pointer)->string.pointer,
		PPI_VERSION_LEN);
	kfree(output.pointer);
	output.length = ACPI_ALLOCATE_BUFFER;
	output.pointer = NULL;
	if (strcmp(version, "1.2") == -1)
		return -EPERM;

	params[2].integer.value = TPM_PPI_FN_GETOPR;
	params[3].package.count = 1;
	obj.type = ACPI_TYPE_INTEGER;
	params[3].package.elements = &obj;
	for (i = start; i <= end; i++) {
		obj.integer.value = i;
		status = acpi_evaluate_object_typed(handle, "_DSM",
			 &input, &output, ACPI_TYPE_INTEGER);
		if (ACPI_FAILURE(status))
			return -ENOMEM;

		ret = ((union acpi_object *)output.pointer)->integer.value;
		if (ret > 0 && ret < ARRAY_SIZE(info))
			str += scnprintf(str, PAGE_SIZE, "%d %d: %s\n",
					 i, ret, info[ret]);
		kfree(output.pointer);
		output.length = ACPI_ALLOCATE_BUFFER;
		output.pointer = NULL;
	}
	return str - buf;
}