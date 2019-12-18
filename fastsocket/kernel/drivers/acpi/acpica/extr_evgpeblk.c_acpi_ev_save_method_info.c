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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  integer; } ;
struct acpi_namespace_node {TYPE_1__ name; } ;
struct TYPE_4__ {struct acpi_namespace_node* method_node; } ;
struct acpi_gpe_event_info {int flags; TYPE_2__ dispatch; } ;
struct acpi_gpe_block_info {scalar_t__ block_base_number; int register_count; struct acpi_gpe_event_info* event_info; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_LOAD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_GPE_DISPATCH_METHOD ; 
 int ACPI_GPE_EDGE_TRIGGERED ; 
 int ACPI_GPE_LEVEL_TRIGGERED ; 
 int ACPI_GPE_TYPE_RUNTIME ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (char*,int /*<<< orphan*/ *) ; 
 int ACPI_NAME_SIZE ; 
 scalar_t__ ACPI_STRTOUL (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  acpi_ev_enable_gpe (struct acpi_gpe_event_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_save_method_info ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ev_save_method_info(acpi_handle obj_handle,
			 u32 level, void *obj_desc, void **return_value)
{
	struct acpi_gpe_block_info *gpe_block = (void *)obj_desc;
	struct acpi_gpe_event_info *gpe_event_info;
	u32 gpe_number;
	char name[ACPI_NAME_SIZE + 1];
	u8 type;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_save_method_info);

	/*
	 * _Lxx and _Exx GPE method support
	 *
	 * 1) Extract the name from the object and convert to a string
	 */
	ACPI_MOVE_32_TO_32(name,
			   &((struct acpi_namespace_node *)obj_handle)->name.
			   integer);
	name[ACPI_NAME_SIZE] = 0;

	/*
	 * 2) Edge/Level determination is based on the 2nd character
	 *    of the method name
	 *
	 * NOTE: Default GPE type is RUNTIME. May be changed later to WAKE
	 * if a _PRW object is found that points to this GPE.
	 */
	switch (name[1]) {
	case 'L':
		type = ACPI_GPE_LEVEL_TRIGGERED;
		break;

	case 'E':
		type = ACPI_GPE_EDGE_TRIGGERED;
		break;

	default:
		/* Unknown method type, just ignore it! */

		ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
				  "Ignoring unknown GPE method type: %s "
				  "(name not of form _Lxx or _Exx)", name));
		return_ACPI_STATUS(AE_OK);
	}

	/* Convert the last two characters of the name to the GPE Number */

	gpe_number = ACPI_STRTOUL(&name[2], NULL, 16);
	if (gpe_number == ACPI_UINT32_MAX) {

		/* Conversion failed; invalid method, just ignore it */

		ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
				  "Could not extract GPE number from name: %s "
				  "(name is not of form _Lxx or _Exx)", name));
		return_ACPI_STATUS(AE_OK);
	}

	/* Ensure that we have a valid GPE number for this GPE block */

	if ((gpe_number < gpe_block->block_base_number) ||
	    (gpe_number >= (gpe_block->block_base_number +
			    (gpe_block->register_count * 8)))) {
		/*
		 * Not valid for this GPE block, just ignore it. However, it may be
		 * valid for a different GPE block, since GPE0 and GPE1 methods both
		 * appear under \_GPE.
		 */
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * Now we can add this information to the gpe_event_info block for use
	 * during dispatch of this GPE. Default type is RUNTIME, although this may
	 * change when the _PRW methods are executed later.
	 */
	gpe_event_info =
	    &gpe_block->event_info[gpe_number - gpe_block->block_base_number];

	gpe_event_info->flags = (u8)
	    (type | ACPI_GPE_DISPATCH_METHOD | ACPI_GPE_TYPE_RUNTIME);

	gpe_event_info->dispatch.method_node =
	    (struct acpi_namespace_node *)obj_handle;

	/* Update enable mask, but don't enable the HW GPE as of yet */

	status = acpi_ev_enable_gpe(gpe_event_info, FALSE);

	ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
			  "Registered GPE method %s as GPE number 0x%.2X\n",
			  name, gpe_number));
	return_ACPI_STATUS(status);
}