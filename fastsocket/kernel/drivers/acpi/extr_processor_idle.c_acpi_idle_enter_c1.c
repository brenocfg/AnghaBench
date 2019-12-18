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
struct cpuidle_state {int dummy; } ;
struct cpuidle_device {int dummy; } ;
struct acpi_processor_cx {int /*<<< orphan*/  usage; } ;
struct acpi_processor {int dummy; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 struct acpi_processor* __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_idle_do_entry (struct acpi_processor_cx*) ; 
 scalar_t__ acpi_idle_suspend ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct acpi_processor_cx* cpuidle_get_statedata (struct cpuidle_state*) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_timer_state_broadcast (struct acpi_processor*,struct acpi_processor_cx*,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  processors ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int acpi_idle_enter_c1(struct cpuidle_device *dev,
			      struct cpuidle_state *state)
{
	ktime_t  kt1, kt2;
	s64 idle_time;
	struct acpi_processor *pr;
	struct acpi_processor_cx *cx = cpuidle_get_statedata(state);

	pr = __get_cpu_var(processors);

	if (unlikely(!pr))
		return 0;

	local_irq_disable();

	/* Do not access any ACPI IO ports in suspend path */
	if (acpi_idle_suspend) {
		local_irq_enable();
		cpu_relax();
		return 0;
	}

	lapic_timer_state_broadcast(pr, cx, 1);
	kt1 = ktime_get_real();
	acpi_idle_do_entry(cx);
	kt2 = ktime_get_real();
	idle_time =  ktime_to_us(ktime_sub(kt2, kt1));

	local_irq_enable();
	cx->usage++;
	lapic_timer_state_broadcast(pr, cx, 0);

	return idle_time;
}