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
struct TYPE_5__ {int /*<<< orphan*/ * pointer; scalar_t__ length; } ;
struct TYPE_4__ {int /*<<< orphan*/  pointer; } ;
union acpi_object {TYPE_3__ integer; TYPE_2__ buffer; int /*<<< orphan*/  type; TYPE_1__ string; } ;
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {int /*<<< orphan*/ * pointer; int /*<<< orphan*/  length; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PPI_VERSION_LEN ; 
 int TPM_PPI_FN_GETACT ; 
 int /*<<< orphan*/  TPM_PPI_FN_VERSION ; 
 int /*<<< orphan*/  acpi_evaluate_object_typed (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppi_assign_params (union acpi_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppi_callback ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_device_name ; 

__attribute__((used)) static ssize_t tpm_show_ppi_transition_action(struct device *dev,
					      struct device_attribute *attr,
					      char *buf)
{
	char version[PPI_VERSION_LEN + 1];
	acpi_handle handle;
	acpi_status status;
	struct acpi_object_list input;
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object params[4];
	u32 ret;
	char *info[] = {
		"None",
		"Shutdown",
		"Reboot",
		"OS Vendor-specific",
		"Error",
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
	/*
	 * PPI spec defines params[3].type as empty package, but some platforms
	 * (e.g. Capella with PPI 1.0) need integer/string/buffer type, so for
	 * compatibility, define params[3].type as buffer, if PPI version < 1.2
	 */
	if (strcmp(version, "1.2") == -1) {
		params[3].type = ACPI_TYPE_BUFFER;
		params[3].buffer.length =  0;
		params[3].buffer.pointer = NULL;
	}
	params[2].integer.value = TPM_PPI_FN_GETACT;
	kfree(output.pointer);
	output.length = ACPI_ALLOCATE_BUFFER;
	output.pointer = NULL;
	status = acpi_evaluate_object_typed(handle, "_DSM", &input, &output,
					    ACPI_TYPE_INTEGER);
	if (ACPI_FAILURE(status))
		return -ENOMEM;
	ret = ((union acpi_object *)output.pointer)->integer.value;
	if (ret < ARRAY_SIZE(info) - 1)
		status = scnprintf(buf, PAGE_SIZE, "%d: %s\n", ret, info[ret]);
	else
		status = scnprintf(buf, PAGE_SIZE, "%d: %s\n", ret,
				   info[ARRAY_SIZE(info)-1]);
	kfree(output.pointer);
	return status;
}