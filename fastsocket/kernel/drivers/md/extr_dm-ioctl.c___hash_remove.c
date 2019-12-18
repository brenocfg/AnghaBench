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
struct hash_cell {int /*<<< orphan*/  md; scalar_t__ new_map; int /*<<< orphan*/  name_list; int /*<<< orphan*/  uuid_list; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 struct dm_table* dm_get_live_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_hash_cells_mutex ; 
 int /*<<< orphan*/  dm_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_set_mdptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_table_destroy (scalar_t__) ; 
 int /*<<< orphan*/  dm_table_event (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_put (struct dm_table*) ; 
 int /*<<< orphan*/  free_cell (struct hash_cell*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __hash_remove(struct hash_cell *hc)
{
	struct dm_table *table;

	/* remove from the dev hash */
	list_del(&hc->uuid_list);
	list_del(&hc->name_list);
	mutex_lock(&dm_hash_cells_mutex);
	dm_set_mdptr(hc->md, NULL);
	mutex_unlock(&dm_hash_cells_mutex);

	table = dm_get_live_table(hc->md);
	if (table) {
		dm_table_event(table);
		dm_table_put(table);
	}

	if (hc->new_map)
		dm_table_destroy(hc->new_map);
	dm_put(hc->md);
	free_cell(hc);
}