#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ id; int /*<<< orphan*/ * name; int /*<<< orphan*/ * proc_entry; } ;
typedef  TYPE_1__ srm_env_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BASE_DIR ; 
 int /*<<< orphan*/ * NAMED_DIR ; 
 int /*<<< orphan*/ * NUMBERED_DIR ; 
 int /*<<< orphan*/ * base_dir ; 
 int /*<<< orphan*/ * named_dir ; 
 int /*<<< orphan*/ * numbered_dir ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* srm_named_entries ; 
 TYPE_1__* srm_numbered_entries ; 

__attribute__((used)) static void
srm_env_cleanup(void)
{
	srm_env_t	*entry;
	unsigned long	var_num;

	if (base_dir) {
		/*
		 * Remove named entries
		 */
		if (named_dir) {
			entry = srm_named_entries;
			while (entry->name != NULL && entry->id != 0) {
				if (entry->proc_entry) {
					remove_proc_entry(entry->name,
							named_dir);
					entry->proc_entry = NULL;
				}
				entry++;
			}
			remove_proc_entry(NAMED_DIR, base_dir);
		}

		/*
		 * Remove numbered entries
		 */
		if (numbered_dir) {
			for (var_num = 0; var_num <= 255; var_num++) {
				entry =	&srm_numbered_entries[var_num];

				if (entry->proc_entry) {
					remove_proc_entry(entry->name,
							numbered_dir);
					entry->proc_entry	= NULL;
					entry->name		= NULL;
				}
			}
			remove_proc_entry(NUMBERED_DIR, base_dir);
		}

		remove_proc_entry(BASE_DIR, NULL);
	}

	return;
}