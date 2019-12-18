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
typedef  scalar_t__ u32 ;
struct acpi_gpe_xrupt_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * handler; } ;
struct acpi_gpe_event_info {int flags; TYPE_1__ dispatch; } ;
struct acpi_gpe_block_info {scalar_t__ register_count; struct acpi_gpe_event_info* event_info; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_GPE_DISPATCH_HANDLER ; 
 int ACPI_GPE_DISPATCH_MASK ; 
 scalar_t__ ACPI_GPE_REGISTER_WIDTH ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ev_delete_gpe_handlers ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_delete_gpe_handlers(struct acpi_gpe_xrupt_info *gpe_xrupt_info,
			    struct acpi_gpe_block_info *gpe_block,
			    void *context)
{
	struct acpi_gpe_event_info *gpe_event_info;
	u32 i;
	u32 j;

	ACPI_FUNCTION_TRACE(ev_delete_gpe_handlers);

	/* Examine each GPE Register within the block */

	for (i = 0; i < gpe_block->register_count; i++) {

		/* Now look at the individual GPEs in this byte register */

		for (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++) {
			gpe_event_info = &gpe_block->event_info[((acpi_size) i *
								 ACPI_GPE_REGISTER_WIDTH)
								+ j];

			if ((gpe_event_info->flags & ACPI_GPE_DISPATCH_MASK) ==
			    ACPI_GPE_DISPATCH_HANDLER) {
				ACPI_FREE(gpe_event_info->dispatch.handler);
				gpe_event_info->dispatch.handler = NULL;
				gpe_event_info->flags &=
				    ~ACPI_GPE_DISPATCH_MASK;
			}
		}
	}

	return_ACPI_STATUS(AE_OK);
}