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
typedef  int u32 ;
struct TYPE_4__ {int* pointer; size_t length; } ;
struct TYPE_3__ {int length; int* pointer; } ;
struct acpi_osc_context {int rev; TYPE_2__ ret; TYPE_1__ cap; int /*<<< orphan*/  uuid_str; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int OSC_QUERY_ENABLE ; 
 size_t OSC_QUERY_TYPE ; 
 int OSC_SB_APEI_SUPPORT ; 
 int OSC_SB_HOTPLUG_OST_SUPPORT ; 
 int OSC_SB_PAD_SUPPORT ; 
 int OSC_SB_PPC_OST_SUPPORT ; 
 int OSC_SB_PR3_SUPPORT ; 
 size_t OSC_SUPPORT_TYPE ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_run_osc (int /*<<< orphan*/ ,struct acpi_osc_context*) ; 
 int /*<<< orphan*/  ghes_disable ; 
 scalar_t__ is_kdump_kernel () ; 
 scalar_t__ is_uv_system () ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int osc_sb_apei_support_acked ; 
 int /*<<< orphan*/  sb_uuid_str ; 

__attribute__((used)) static void acpi_bus_osc_support(void)
{
	u32 capbuf[2];
	struct acpi_osc_context context = {
		.uuid_str = sb_uuid_str,
		.rev = 1,
		.cap.length = 8,
		.cap.pointer = capbuf,
	};
	acpi_handle handle;

	capbuf[OSC_QUERY_TYPE] = OSC_QUERY_ENABLE;
	capbuf[OSC_SUPPORT_TYPE] = OSC_SB_PR3_SUPPORT; /* _PR3 is in use */
#if defined(CONFIG_ACPI_PROCESSOR_AGGREGATOR) ||\
			defined(CONFIG_ACPI_PROCESSOR_AGGREGATOR_MODULE)
	capbuf[OSC_SUPPORT_TYPE] |= OSC_SB_PAD_SUPPORT;
#endif

#if defined(CONFIG_ACPI_PROCESSOR) || defined(CONFIG_ACPI_PROCESSOR_MODULE)
	capbuf[OSC_SUPPORT_TYPE] |= OSC_SB_PPC_OST_SUPPORT;
#endif

#ifdef ACPI_HOTPLUG_OST
	capbuf[OSC_SUPPORT_TYPE] |= OSC_SB_HOTPLUG_OST_SUPPORT;
#endif

	if (!ghes_disable)
		capbuf[OSC_SUPPORT_TYPE] |= OSC_SB_APEI_SUPPORT;
	if (ACPI_FAILURE(acpi_get_handle(NULL, "\\_SB", &handle)))
		return;

	if (is_uv_system() && is_kdump_kernel()) {
		/*
		 * There is no need to parse the OS Capabilities table
		 * in the crash kernel. And it should not be done, as
		 * that parsing includes destructive writes to io ports to
		 * initialize UV system controller interrupts.
		 */
		return;
	}

	if (ACPI_SUCCESS(acpi_run_osc(handle, &context))) {
		u32 *capbuf_ret = context.ret.pointer;
		if (context.ret.length > OSC_SUPPORT_TYPE)
			osc_sb_apei_support_acked =
				capbuf_ret[OSC_SUPPORT_TYPE] & OSC_SB_APEI_SUPPORT;
		kfree(context.ret.pointer);
	}
	/* do we need to check other returned cap? Sounds no */
}