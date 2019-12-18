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
struct hash_cell {struct mapped_device* md; int /*<<< orphan*/ * new_map; } ;
struct dm_ioctl {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMDEBUG_LIMIT (char*) ; 
 int /*<<< orphan*/  DM_INACTIVE_PRESENT_FLAG ; 
 int ENXIO ; 
 int /*<<< orphan*/  __dev_status (struct mapped_device*,struct dm_ioctl*) ; 
 struct hash_cell* __find_device_hash_cell (struct dm_ioctl*) ; 
 int /*<<< orphan*/  _hash_lock ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int table_clear(struct dm_ioctl *param, size_t param_size)
{
	struct hash_cell *hc;
	struct mapped_device *md;

	down_write(&_hash_lock);

	hc = __find_device_hash_cell(param);
	if (!hc) {
		DMDEBUG_LIMIT("device doesn't appear to be in the dev hash table.");
		up_write(&_hash_lock);
		return -ENXIO;
	}

	if (hc->new_map) {
		dm_table_destroy(hc->new_map);
		hc->new_map = NULL;
	}

	param->flags &= ~DM_INACTIVE_PRESENT_FLAG;

	__dev_status(hc->md, param);
	md = hc->md;
	up_write(&_hash_lock);
	dm_put(md);

	return 0;
}