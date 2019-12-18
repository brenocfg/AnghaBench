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
typedef  char u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_4__ {int length; int* pointer; } ;
struct acpi_osc_context {char* uuid_str; int rev; TYPE_1__ ret; TYPE_2__ cap; } ;
typedef  int /*<<< orphan*/  capbuf ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 size_t OSC_CONTROL_TYPE ; 
 int OSC_QUERY_ENABLE ; 
 size_t OSC_QUERY_TYPE ; 
 size_t OSC_SUPPORT_TYPE ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_run_osc (int /*<<< orphan*/ ,struct acpi_osc_context*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

int apei_osc_setup(void)
{
	static u8 whea_uuid_str[] = "ed855e0c-6c90-47bf-a62a-26de0fc5ad5c";
	acpi_handle handle;
	u32 capbuf[3];
	struct acpi_osc_context context = {
		.uuid_str	= whea_uuid_str,
		.rev		= 1,
		.cap.length	= sizeof(capbuf),
		.cap.pointer	= capbuf,
	};

	capbuf[OSC_QUERY_TYPE] = OSC_QUERY_ENABLE;
	capbuf[OSC_SUPPORT_TYPE] = 1;
	capbuf[OSC_CONTROL_TYPE] = 0;

	if (ACPI_FAILURE(acpi_get_handle(NULL, "\\_SB", &handle))
	    || ACPI_FAILURE(acpi_run_osc(handle, &context)))
		return -EIO;
	else {
		kfree(context.ret.pointer);
		return 0;
	}
}