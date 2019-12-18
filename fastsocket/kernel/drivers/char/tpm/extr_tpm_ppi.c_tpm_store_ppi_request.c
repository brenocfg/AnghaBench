#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int value; } ;
struct TYPE_7__ {int count; union acpi_object* elements; } ;
struct TYPE_6__ {int length; char* pointer; } ;
struct TYPE_5__ {int /*<<< orphan*/  pointer; } ;
union acpi_object {TYPE_4__ integer; TYPE_3__ package; int /*<<< orphan*/  type; TYPE_2__ buffer; TYPE_1__ string; } ;
typedef  int u64 ;
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {int /*<<< orphan*/ * pointer; int /*<<< orphan*/  length; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  req ;
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
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  PPI_VERSION_LEN ; 
 int TPM_PPI_FN_SUBREQ ; 
 int TPM_PPI_FN_SUBREQ2 ; 
 int /*<<< orphan*/  TPM_PPI_FN_VERSION ; 
 int /*<<< orphan*/  acpi_evaluate_object_typed (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppi_assign_params (union acpi_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppi_callback ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 
 int strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_device_name ; 

__attribute__((used)) static ssize_t tpm_store_ppi_request(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	char version[PPI_VERSION_LEN + 1];
	acpi_handle handle;
	acpi_status status;
	struct acpi_object_list input;
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object params[4];
	union acpi_object obj;
	u32 req;
	u64 ret;

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
	/*
	 * the function to submit TPM operation request to pre-os environment
	 * is updated with function index from SUBREQ to SUBREQ2 since PPI
	 * version 1.1
	 */
	if (strcmp(version, "1.1") == -1)
		params[2].integer.value = TPM_PPI_FN_SUBREQ;
	else
		params[2].integer.value = TPM_PPI_FN_SUBREQ2;
	/*
	 * PPI spec defines params[3].type as ACPI_TYPE_PACKAGE. Some BIOS
	 * accept buffer/string/integer type, but some BIOS accept buffer/
	 * string/package type. For PPI version 1.0 and 1.1, use buffer type
	 * for compatibility, and use package type since 1.2 according to spec.
	 */
	if (strcmp(version, "1.2") == -1) {
		params[3].type = ACPI_TYPE_BUFFER;
		params[3].buffer.length = sizeof(req);
		sscanf(buf, "%d", &req);
		params[3].buffer.pointer = (char *)&req;
	} else {
		params[3].package.count = 1;
		obj.type = ACPI_TYPE_INTEGER;
		sscanf(buf, "%llu", &obj.integer.value);
		params[3].package.elements = &obj;
	}

	status = acpi_evaluate_object_typed(handle, "_DSM", &input, &output,
					    ACPI_TYPE_INTEGER);
	if (ACPI_FAILURE(status))
		return -ENOMEM;
	ret = ((union acpi_object *)output.pointer)->integer.value;
	if (ret == 0)
		status = (acpi_status)count;
	else if (ret == 1)
		status = -EPERM;
	else
		status = -EFAULT;
	kfree(output.pointer);
	return status;
}