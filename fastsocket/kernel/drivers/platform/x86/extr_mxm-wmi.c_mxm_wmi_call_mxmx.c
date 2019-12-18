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
struct mxds_args {int xarg; int /*<<< orphan*/  args; int /*<<< orphan*/  func; } ;
struct acpi_buffer {struct mxds_args* member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  args ;
typedef  int acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int) ; 
 int /*<<< orphan*/  MXM_WMMX_FUNC_MXMX ; 
 int /*<<< orphan*/  MXM_WMMX_GUID ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int wmi_evaluate_method (int /*<<< orphan*/ ,int,int,struct acpi_buffer*,struct acpi_buffer*) ; 

int mxm_wmi_call_mxmx(int adapter)
{
	struct mxds_args args = {
		.func = MXM_WMMX_FUNC_MXMX,
		.args = 0,
		.xarg = 1,
	};
	struct acpi_buffer input = { (acpi_size)sizeof(args), &args };
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };
	acpi_status status;

	printk("calling mux switch %d\n", adapter);

	status = wmi_evaluate_method(MXM_WMMX_GUID, 0x1, adapter, &input,
				     &output);

	if (ACPI_FAILURE(status))
		return status;

	printk("mux mutex set switched %d\n", status);
	return 0;
			    
}