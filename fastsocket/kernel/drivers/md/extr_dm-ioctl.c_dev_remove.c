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
struct hash_cell {int /*<<< orphan*/  name; struct mapped_device* md; } ;
struct dm_ioctl {int /*<<< orphan*/  flags; int /*<<< orphan*/  event_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMDEBUG_LIMIT (char*,...) ; 
 int /*<<< orphan*/  DM_UEVENT_GENERATED_FLAG ; 
 int ENXIO ; 
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 struct hash_cell* __find_device_hash_cell (struct dm_ioctl*) ; 
 int /*<<< orphan*/  __hash_remove (struct hash_cell*) ; 
 int /*<<< orphan*/  _hash_lock ; 
 int /*<<< orphan*/  dm_destroy (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_kobject_uevent (struct mapped_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dm_lock_for_deletion (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dev_remove(struct dm_ioctl *param, size_t param_size)
{
	struct hash_cell *hc;
	struct mapped_device *md;
	int r;

	down_write(&_hash_lock);
	hc = __find_device_hash_cell(param);

	if (!hc) {
		DMDEBUG_LIMIT("device doesn't appear to be in the dev hash table.");
		up_write(&_hash_lock);
		return -ENXIO;
	}

	md = hc->md;

	/*
	 * Ensure the device is not open and nothing further can open it.
	 */
	r = dm_lock_for_deletion(md);
	if (r) {
		DMDEBUG_LIMIT("unable to remove open device %s", hc->name);
		up_write(&_hash_lock);
		dm_put(md);
		return r;
	}

	__hash_remove(hc);
	up_write(&_hash_lock);

	if (!dm_kobject_uevent(md, KOBJ_REMOVE, param->event_nr))
		param->flags |= DM_UEVENT_GENERATED_FLAG;

	dm_put(md);
	dm_destroy(md);
	return 0;
}