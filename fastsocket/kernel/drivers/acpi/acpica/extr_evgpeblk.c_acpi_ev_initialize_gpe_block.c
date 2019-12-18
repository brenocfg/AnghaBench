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
typedef  scalar_t__ u32 ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_gpe_walk_info {struct acpi_namespace_node* gpe_device; struct acpi_gpe_block_info* gpe_block; } ;
struct acpi_gpe_event_info {int flags; } ;
struct acpi_gpe_block_info {scalar_t__ register_count; struct acpi_gpe_event_info* event_info; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_GPE_DISPATCH_MASK ; 
 int ACPI_GPE_DISPATCH_METHOD ; 
 scalar_t__ ACPI_GPE_REGISTER_WIDTH ; 
 int ACPI_GPE_TYPE_RUNTIME ; 
 int ACPI_GPE_TYPE_WAKE ; 
 int /*<<< orphan*/  ACPI_NS_WALK_UNLOCK ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ev_match_prw_and_gpe ; 
 scalar_t__ acpi_gbl_leave_wake_gpes_disabled ; 
 int /*<<< orphan*/  acpi_hw_enable_runtime_gpe_block (int /*<<< orphan*/ *,struct acpi_gpe_block_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ns_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_gpe_walk_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_initialize_gpe_block ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_initialize_gpe_block(struct acpi_namespace_node *gpe_device,
			     struct acpi_gpe_block_info *gpe_block)
{
	acpi_status status;
	struct acpi_gpe_event_info *gpe_event_info;
	struct acpi_gpe_walk_info gpe_info;
	u32 wake_gpe_count;
	u32 gpe_enabled_count;
	u32 i;
	u32 j;

	ACPI_FUNCTION_TRACE(ev_initialize_gpe_block);

	/* Ignore a null GPE block (e.g., if no GPE block 1 exists) */

	if (!gpe_block) {
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * Runtime option: Should wake GPEs be enabled at runtime?  The default
	 * is no, they should only be enabled just as the machine goes to sleep.
	 */
	if (acpi_gbl_leave_wake_gpes_disabled) {
		/*
		 * Differentiate runtime vs wake GPEs, via the _PRW control methods.
		 * Each GPE that has one or more _PRWs that reference it is by
		 * definition a wake GPE and will not be enabled while the machine
		 * is running.
		 */
		gpe_info.gpe_block = gpe_block;
		gpe_info.gpe_device = gpe_device;

		status =
		    acpi_ns_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
					   ACPI_UINT32_MAX, ACPI_NS_WALK_UNLOCK,
					   acpi_ev_match_prw_and_gpe, &gpe_info,
					   NULL);
	}

	/*
	 * Enable all GPEs in this block that have these attributes:
	 * 1) are "runtime" or "run/wake" GPEs, and
	 * 2) have a corresponding _Lxx or _Exx method
	 *
	 * Any other GPEs within this block must be enabled via the
	 * acpi_enable_gpe() external interface.
	 */
	wake_gpe_count = 0;
	gpe_enabled_count = 0;

	for (i = 0; i < gpe_block->register_count; i++) {
		for (j = 0; j < 8; j++) {

			/* Get the info block for this particular GPE */

			gpe_event_info = &gpe_block->event_info[((acpi_size) i *
								 ACPI_GPE_REGISTER_WIDTH)
								+ j];

			if (((gpe_event_info->flags & ACPI_GPE_DISPATCH_MASK) ==
			     ACPI_GPE_DISPATCH_METHOD) &&
			    (gpe_event_info->flags & ACPI_GPE_TYPE_RUNTIME)) {
				gpe_enabled_count++;
			}

			if (gpe_event_info->flags & ACPI_GPE_TYPE_WAKE) {
				wake_gpe_count++;
			}
		}
	}

	ACPI_DEBUG_PRINT((ACPI_DB_INIT,
			  "Found %u Wake, Enabled %u Runtime GPEs in this block\n",
			  wake_gpe_count, gpe_enabled_count));

	/* Enable all valid runtime GPEs found above */

	status = acpi_hw_enable_runtime_gpe_block(NULL, gpe_block, NULL);
	if (ACPI_FAILURE(status)) {
		ACPI_ERROR((AE_INFO, "Could not enable GPEs in GpeBlock %p",
			    gpe_block));
	}

	return_ACPI_STATUS(status);
}