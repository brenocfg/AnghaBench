#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* prev; struct TYPE_6__* next; int /*<<< orphan*/  debugfs_root_entry; int /*<<< orphan*/ * debugfs_entries; int /*<<< orphan*/ * views; int /*<<< orphan*/  ref_count; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 int DEBUG_MAX_VIEWS ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 TYPE_1__* debug_area_first ; 
 TYPE_1__* debug_area_last ; 
 int /*<<< orphan*/  debug_info_free (TYPE_1__*) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
debug_info_put(debug_info_t *db_info)
{
	int i;

	if (!db_info)
		return;
	if (atomic_dec_and_test(&db_info->ref_count)) {
		for (i = 0; i < DEBUG_MAX_VIEWS; i++) {
			if (!db_info->views[i])
				continue;
			debugfs_remove(db_info->debugfs_entries[i]);
		}
		debugfs_remove(db_info->debugfs_root_entry);
		if(db_info == debug_area_first)
			debug_area_first = db_info->next;
		if(db_info == debug_area_last)
			debug_area_last = db_info->prev;
		if(db_info->prev) db_info->prev->next = db_info->next;
		if(db_info->next) db_info->next->prev = db_info->prev;
		debug_info_free(db_info);
	}
}