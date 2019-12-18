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
struct xt_table_info {scalar_t__ number; scalar_t__ initial_entries; int /*<<< orphan*/  size; void** entries; } ;
struct xt_table {struct module* me; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6T_ENTRY_ITERATE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_entry ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 size_t raw_smp_processor_id () ; 
 int /*<<< orphan*/  xt_free_table_info (struct xt_table_info*) ; 
 struct xt_table_info* xt_unregister_table (struct xt_table*) ; 

void ip6t_unregister_table(struct xt_table *table)
{
	struct xt_table_info *private;
	void *loc_cpu_entry;
	struct module *table_owner = table->me;

	private = xt_unregister_table(table);

	/* Decrease module usage counts and free resources */
	loc_cpu_entry = private->entries[raw_smp_processor_id()];
	IP6T_ENTRY_ITERATE(loc_cpu_entry, private->size, cleanup_entry, NULL);
	if (private->number > private->initial_entries)
		module_put(table_owner);
	xt_free_table_info(private);
}