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
struct acpi_einj_trigger {int header_size; int table_size; int entry_count; } ;
struct acpi_einj_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 

__attribute__((used)) static int einj_check_trigger_header(struct acpi_einj_trigger *trigger_tab)
{
	if (trigger_tab->header_size != sizeof(struct acpi_einj_trigger))
		return -EINVAL;
	if (trigger_tab->table_size > PAGE_SIZE ||
	    trigger_tab->table_size < trigger_tab->header_size)
		return -EINVAL;
	if (trigger_tab->entry_count !=
	    (trigger_tab->table_size - trigger_tab->header_size) /
	    sizeof(struct acpi_einj_entry))
		return -EINVAL;

	return 0;
}