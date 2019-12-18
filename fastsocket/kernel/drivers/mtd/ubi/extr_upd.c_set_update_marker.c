#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubi_vtbl_record {int upd_marker; } ;
struct ubi_volume {size_t vol_id; int upd_marker; } ;
struct ubi_device {int /*<<< orphan*/  device_mutex; TYPE_1__* vtbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  upd_marker; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_gen (char*,...) ; 
 int /*<<< orphan*/  memcpy (struct ubi_vtbl_record*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int /*<<< orphan*/ ) ; 
 int ubi_change_vtbl_record (struct ubi_device*,size_t,struct ubi_vtbl_record*) ; 

__attribute__((used)) static int set_update_marker(struct ubi_device *ubi, struct ubi_volume *vol)
{
	int err;
	struct ubi_vtbl_record vtbl_rec;

	dbg_gen("set update marker for volume %d", vol->vol_id);

	if (vol->upd_marker) {
		ubi_assert(ubi->vtbl[vol->vol_id].upd_marker);
		dbg_gen("already set");
		return 0;
	}

	memcpy(&vtbl_rec, &ubi->vtbl[vol->vol_id],
	       sizeof(struct ubi_vtbl_record));
	vtbl_rec.upd_marker = 1;

	mutex_lock(&ubi->device_mutex);
	err = ubi_change_vtbl_record(ubi, vol->vol_id, &vtbl_rec);
	vol->upd_marker = 1;
	mutex_unlock(&ubi->device_mutex);
	return err;
}