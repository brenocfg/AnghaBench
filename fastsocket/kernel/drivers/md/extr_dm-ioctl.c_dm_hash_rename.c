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
struct mapped_device {int dummy; } ;
struct hash_cell {char const* uuid; struct mapped_device* md; } ;
struct dm_table {int dummy; } ;
struct dm_ioctl {int flags; char const* name; int /*<<< orphan*/  event_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,char*,char const*,char const*) ; 
 int DM_UEVENT_GENERATED_FLAG ; 
 int DM_UUID_FLAG ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 struct mapped_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 char* __change_cell_name (struct hash_cell*,char*) ; 
 struct hash_cell* __get_name_cell (char const*) ; 
 struct hash_cell* __get_uuid_cell (char const*) ; 
 int /*<<< orphan*/  __set_cell_uuid (struct hash_cell*,char*) ; 
 int /*<<< orphan*/  _hash_lock ; 
 struct dm_table* dm_get_live_table (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_kobject_uevent (struct mapped_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_event (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_put (struct dm_table*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mapped_device *dm_hash_rename(struct dm_ioctl *param,
					    const char *new)
{
	char *new_data, *old_name = NULL;
	struct hash_cell *hc;
	struct dm_table *table;
	struct mapped_device *md;
	unsigned change_uuid = (param->flags & DM_UUID_FLAG) ? 1 : 0;

	/*
	 * duplicate new.
	 */
	new_data = kstrdup(new, GFP_KERNEL);
	if (!new_data)
		return ERR_PTR(-ENOMEM);

	down_write(&_hash_lock);

	/*
	 * Is new free ?
	 */
	if (change_uuid)
		hc = __get_uuid_cell(new);
	else
		hc = __get_name_cell(new);

	if (hc) {
		DMWARN("Unable to change %s on mapped device %s to one that "
		       "already exists: %s",
		       change_uuid ? "uuid" : "name",
		       param->name, new);
		dm_put(hc->md);
		up_write(&_hash_lock);
		kfree(new_data);
		return ERR_PTR(-EBUSY);
	}

	/*
	 * Is there such a device as 'old' ?
	 */
	hc = __get_name_cell(param->name);
	if (!hc) {
		DMWARN("Unable to rename non-existent device, %s to %s%s",
		       param->name, change_uuid ? "uuid " : "", new);
		up_write(&_hash_lock);
		kfree(new_data);
		return ERR_PTR(-ENXIO);
	}

	/*
	 * Does this device already have a uuid?
	 */
	if (change_uuid && hc->uuid) {
		DMWARN("Unable to change uuid of mapped device %s to %s "
		       "because uuid is already set to %s",
		       param->name, new, hc->uuid);
		dm_put(hc->md);
		up_write(&_hash_lock);
		kfree(new_data);
		return ERR_PTR(-EINVAL);
	}

	if (change_uuid)
		__set_cell_uuid(hc, new_data);
	else
		old_name = __change_cell_name(hc, new_data);

	/*
	 * Wake up any dm event waiters.
	 */
	table = dm_get_live_table(hc->md);
	if (table) {
		dm_table_event(table);
		dm_table_put(table);
	}

	if (!dm_kobject_uevent(hc->md, KOBJ_CHANGE, param->event_nr))
		param->flags |= DM_UEVENT_GENERATED_FLAG;

	md = hc->md;
	up_write(&_hash_lock);
	kfree(old_name);

	return md;
}