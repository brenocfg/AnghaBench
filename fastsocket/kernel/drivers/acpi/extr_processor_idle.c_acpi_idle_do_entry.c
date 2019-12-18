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
struct acpi_processor_cx {scalar_t__ entry_method; int /*<<< orphan*/  address; } ;
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
struct TYPE_4__ {TYPE_1__ xpm_timer_block; } ;

/* Variables and functions */
 scalar_t__ ACPI_CSTATE_FFH ; 
 scalar_t__ ACPI_CSTATE_HALT ; 
 TYPE_2__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_processor_ffh_cstate_enter (struct acpi_processor_cx*) ; 
 int /*<<< orphan*/  acpi_safe_halt () ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_critical_timings () ; 
 int /*<<< orphan*/  stop_critical_timings () ; 

__attribute__((used)) static inline void acpi_idle_do_entry(struct acpi_processor_cx *cx)
{
	/* Don't trace irqs off for idle */
	stop_critical_timings();
	if (cx->entry_method == ACPI_CSTATE_FFH) {
		/* Call into architectural FFH based C-state */
		acpi_processor_ffh_cstate_enter(cx);
	} else if (cx->entry_method == ACPI_CSTATE_HALT) {
		acpi_safe_halt();
	} else {
		int unused;
		/* IO port based C-state */
		inb(cx->address);
		/* Dummy wait op - must do something useless after P_LVL2 read
		   because chipsets cannot guarantee that STPCLK# signal
		   gets asserted in time to freeze execution properly. */
		unused = inl(acpi_gbl_FADT.xpm_timer_block.address);
	}
	start_critical_timings();
}