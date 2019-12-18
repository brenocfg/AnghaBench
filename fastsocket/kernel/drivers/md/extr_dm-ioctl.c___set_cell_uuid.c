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
struct hash_cell {char* uuid; int /*<<< orphan*/  uuid_list; } ;

/* Variables and functions */
 scalar_t__ _uuid_buckets ; 
 int /*<<< orphan*/  dm_hash_cells_mutex ; 
 scalar_t__ hash_str (char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __set_cell_uuid(struct hash_cell *hc, char *new_uuid)
{
	mutex_lock(&dm_hash_cells_mutex);
	hc->uuid = new_uuid;
	mutex_unlock(&dm_hash_cells_mutex);

	list_add(&hc->uuid_list, _uuid_buckets + hash_str(new_uuid));
}