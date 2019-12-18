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
typedef  int /*<<< orphan*/  u8 ;
struct acpi_gpe_xrupt_info {struct acpi_gpe_xrupt_info* next; struct acpi_gpe_block_info* gpe_block_list_head; } ;
struct acpi_gpe_event_info {int dummy; } ;
struct acpi_gpe_block_info {struct acpi_gpe_block_info* next; scalar_t__ register_count; struct acpi_gpe_event_info* event_info; } ;
typedef  int acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct acpi_gpe_xrupt_info* acpi_gbl_gpe_xrupt_list_head ; 

u8 acpi_ev_valid_gpe_event(struct acpi_gpe_event_info *gpe_event_info)
{
	struct acpi_gpe_xrupt_info *gpe_xrupt_block;
	struct acpi_gpe_block_info *gpe_block;

	ACPI_FUNCTION_ENTRY();

	/* No need for spin lock since we are not changing any list elements */

	/* Walk the GPE interrupt levels */

	gpe_xrupt_block = acpi_gbl_gpe_xrupt_list_head;
	while (gpe_xrupt_block) {
		gpe_block = gpe_xrupt_block->gpe_block_list_head;

		/* Walk the GPE blocks on this interrupt level */

		while (gpe_block) {
			if ((&gpe_block->event_info[0] <= gpe_event_info) &&
			    (&gpe_block->event_info[((acpi_size)
						     gpe_block->
						     register_count) * 8] >
			     gpe_event_info)) {
				return (TRUE);
			}

			gpe_block = gpe_block->next;
		}

		gpe_xrupt_block = gpe_xrupt_block->next;
	}

	return (FALSE);
}