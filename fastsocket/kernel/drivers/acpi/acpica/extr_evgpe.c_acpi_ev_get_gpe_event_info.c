#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct acpi_gpe_block_info* gpe_block; } ;
union acpi_operand_object {TYPE_1__ device; } ;
typedef  size_t u32 ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_gpe_event_info {int dummy; } ;
struct acpi_gpe_block_info {size_t block_base_number; int register_count; struct acpi_gpe_event_info* event_info; } ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 size_t ACPI_MAX_GPE_BLOCKS ; 
 struct acpi_gpe_block_info** acpi_gbl_gpe_fadt_blocks ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 

struct acpi_gpe_event_info *acpi_ev_get_gpe_event_info(acpi_handle gpe_device,
						       u32 gpe_number)
{
	union acpi_operand_object *obj_desc;
	struct acpi_gpe_block_info *gpe_block;
	u32 i;

	ACPI_FUNCTION_ENTRY();

	/* A NULL gpe_block means use the FADT-defined GPE block(s) */

	if (!gpe_device) {

		/* Examine GPE Block 0 and 1 (These blocks are permanent) */

		for (i = 0; i < ACPI_MAX_GPE_BLOCKS; i++) {
			gpe_block = acpi_gbl_gpe_fadt_blocks[i];
			if (gpe_block) {
				if ((gpe_number >= gpe_block->block_base_number)
				    && (gpe_number <
					gpe_block->block_base_number +
					(gpe_block->register_count * 8))) {
					return (&gpe_block->
						event_info[gpe_number -
							   gpe_block->
							   block_base_number]);
				}
			}
		}

		/* The gpe_number was not in the range of either FADT GPE block */

		return (NULL);
	}

	/* A Non-NULL gpe_device means this is a GPE Block Device */

	obj_desc = acpi_ns_get_attached_object((struct acpi_namespace_node *)
					       gpe_device);
	if (!obj_desc || !obj_desc->device.gpe_block) {
		return (NULL);
	}

	gpe_block = obj_desc->device.gpe_block;

	if ((gpe_number >= gpe_block->block_base_number) &&
	    (gpe_number <
	     gpe_block->block_base_number + (gpe_block->register_count * 8))) {
		return (&gpe_block->
			event_info[gpe_number - gpe_block->block_base_number]);
	}

	return (NULL);
}