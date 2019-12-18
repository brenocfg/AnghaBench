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
struct acpi_evaluate_info {TYPE_2__* resolved_node; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_3__ {scalar_t__ integer; } ;
struct TYPE_4__ {TYPE_1__ name; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 scalar_t__ acpi_dbg_layer ; 
 int acpi_dbg_level ; 
 scalar_t__ acpi_gbl_original_dbg_layer ; 
 int acpi_gbl_original_dbg_level ; 
 scalar_t__ acpi_gbl_trace_dbg_layer ; 
 int acpi_gbl_trace_dbg_level ; 
 scalar_t__ acpi_gbl_trace_method_name ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_ps_start_trace(struct acpi_evaluate_info *info)
{
	acpi_status status;

	ACPI_FUNCTION_ENTRY();

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return;
	}

	if ((!acpi_gbl_trace_method_name) ||
	    (acpi_gbl_trace_method_name != info->resolved_node->name.integer)) {
		goto exit;
	}

	acpi_gbl_original_dbg_level = acpi_dbg_level;
	acpi_gbl_original_dbg_layer = acpi_dbg_layer;

	acpi_dbg_level = 0x00FFFFFF;
	acpi_dbg_layer = ACPI_UINT32_MAX;

	if (acpi_gbl_trace_dbg_level) {
		acpi_dbg_level = acpi_gbl_trace_dbg_level;
	}
	if (acpi_gbl_trace_dbg_layer) {
		acpi_dbg_layer = acpi_gbl_trace_dbg_layer;
	}

      exit:
	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
}