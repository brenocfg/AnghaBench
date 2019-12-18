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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_hed_notify_list ; 
 int /*<<< orphan*/  blocking_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 

void unregister_acpi_hed_notifier(struct notifier_block *nb)
{
	blocking_notifier_chain_unregister(&acpi_hed_notify_list, nb);
}