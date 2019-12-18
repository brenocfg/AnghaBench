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
struct acpi_gpe_xrupt_info {scalar_t__ interrupt_number; struct acpi_gpe_xrupt_info* previous; struct acpi_gpe_xrupt_info* next; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_cpu_flags ;
struct TYPE_2__ {scalar_t__ sci_interrupt; } ;

/* Variables and functions */
 struct acpi_gpe_xrupt_info* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_ev_gpe_xrupt_handler ; 
 TYPE_1__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_gbl_gpe_lock ; 
 struct acpi_gpe_xrupt_info* acpi_gbl_gpe_xrupt_list_head ; 
 int /*<<< orphan*/  acpi_os_acquire_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_install_interrupt_handler (scalar_t__,int /*<<< orphan*/ ,struct acpi_gpe_xrupt_info*) ; 
 int /*<<< orphan*/  acpi_os_release_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_get_gpe_xrupt_block ; 
 int /*<<< orphan*/  return_PTR (struct acpi_gpe_xrupt_info*) ; 

__attribute__((used)) static struct acpi_gpe_xrupt_info *acpi_ev_get_gpe_xrupt_block(u32
							       interrupt_number)
{
	struct acpi_gpe_xrupt_info *next_gpe_xrupt;
	struct acpi_gpe_xrupt_info *gpe_xrupt;
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(ev_get_gpe_xrupt_block);

	/* No need for lock since we are not changing any list elements here */

	next_gpe_xrupt = acpi_gbl_gpe_xrupt_list_head;
	while (next_gpe_xrupt) {
		if (next_gpe_xrupt->interrupt_number == interrupt_number) {
			return_PTR(next_gpe_xrupt);
		}

		next_gpe_xrupt = next_gpe_xrupt->next;
	}

	/* Not found, must allocate a new xrupt descriptor */

	gpe_xrupt = ACPI_ALLOCATE_ZEROED(sizeof(struct acpi_gpe_xrupt_info));
	if (!gpe_xrupt) {
		return_PTR(NULL);
	}

	gpe_xrupt->interrupt_number = interrupt_number;

	/* Install new interrupt descriptor with spin lock */

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
	if (acpi_gbl_gpe_xrupt_list_head) {
		next_gpe_xrupt = acpi_gbl_gpe_xrupt_list_head;
		while (next_gpe_xrupt->next) {
			next_gpe_xrupt = next_gpe_xrupt->next;
		}

		next_gpe_xrupt->next = gpe_xrupt;
		gpe_xrupt->previous = next_gpe_xrupt;
	} else {
		acpi_gbl_gpe_xrupt_list_head = gpe_xrupt;
	}
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

	/* Install new interrupt handler if not SCI_INT */

	if (interrupt_number != acpi_gbl_FADT.sci_interrupt) {
		status = acpi_os_install_interrupt_handler(interrupt_number,
							   acpi_ev_gpe_xrupt_handler,
							   gpe_xrupt);
		if (ACPI_FAILURE(status)) {
			ACPI_ERROR((AE_INFO,
				    "Could not install GPE interrupt handler at level 0x%X",
				    interrupt_number));
			return_PTR(NULL);
		}
	}

	return_PTR(gpe_xrupt);
}