#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* acpi_processor_get_throttling ) (struct acpi_processor*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  throttling; } ;
struct acpi_processor {TYPE_2__ throttling; int /*<<< orphan*/  id; TYPE_1__ flags; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;
struct TYPE_7__ {int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int stub1 (struct acpi_processor*) ; 

__attribute__((used)) static int acpi_processor_get_throttling(struct acpi_processor *pr)
{
	cpumask_var_t saved_mask;
	int ret;

	if (!pr)
		return -EINVAL;

	if (!pr->flags.throttling)
		return -ENODEV;

	if (!alloc_cpumask_var(&saved_mask, GFP_KERNEL))
		return -ENOMEM;

	/*
	 * Migrate task to the cpu pointed by pr.
	 */
	cpumask_copy(saved_mask, &current->cpus_allowed);
	/* FIXME: use work_on_cpu() */
	set_cpus_allowed_ptr(current, cpumask_of(pr->id));
	ret = pr->throttling.acpi_processor_get_throttling(pr);
	/* restore the previous state */
	set_cpus_allowed_ptr(current, saved_mask);
	free_cpumask_var(saved_mask);

	return ret;
}