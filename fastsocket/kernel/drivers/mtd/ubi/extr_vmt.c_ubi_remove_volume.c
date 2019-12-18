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
struct ubi_volume_desc {scalar_t__ mode; struct ubi_volume* vol; } ;
struct ubi_volume {int vol_id; int reserved_pebs; int ref_count; int /*<<< orphan*/  cdev; struct ubi_device* ubi; } ;
struct ubi_device {int rsvd_pebs; int avail_pebs; int beb_rsvd_level; int beb_rsvd_pebs; int vol_count; int /*<<< orphan*/  volumes_lock; struct ubi_volume** volumes; scalar_t__ ro_mode; int /*<<< orphan*/  ubi_num; } ;

/* Variables and functions */
 int EBUSY ; 
 int EROFS ; 
 scalar_t__ UBI_EXCLUSIVE ; 
 int /*<<< orphan*/  UBI_VOLUME_REMOVED ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_err (char*,int) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ paranoid_check_volumes (struct ubi_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int ubi_change_vtbl_record (struct ubi_device*,int,int /*<<< orphan*/ *) ; 
 int ubi_eba_unmap_leb (struct ubi_device*,struct ubi_volume*,int) ; 
 int /*<<< orphan*/  ubi_err (char*,int,int) ; 
 int /*<<< orphan*/  ubi_msg (char*,int) ; 
 int /*<<< orphan*/  ubi_volume_notify (struct ubi_device*,struct ubi_volume*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  volume_sysfs_close (struct ubi_volume*) ; 

int ubi_remove_volume(struct ubi_volume_desc *desc, int no_vtbl)
{
	struct ubi_volume *vol = desc->vol;
	struct ubi_device *ubi = vol->ubi;
	int i, err, vol_id = vol->vol_id, reserved_pebs = vol->reserved_pebs;

	dbg_gen("remove device %d, volume %d", ubi->ubi_num, vol_id);
	ubi_assert(desc->mode == UBI_EXCLUSIVE);
	ubi_assert(vol == ubi->volumes[vol_id]);

	if (ubi->ro_mode)
		return -EROFS;

	spin_lock(&ubi->volumes_lock);
	if (vol->ref_count > 1) {
		/*
		 * The volume is busy, probably someone is reading one of its
		 * sysfs files.
		 */
		err = -EBUSY;
		goto out_unlock;
	}
	ubi->volumes[vol_id] = NULL;
	spin_unlock(&ubi->volumes_lock);

	if (!no_vtbl) {
		err = ubi_change_vtbl_record(ubi, vol_id, NULL);
		if (err)
			goto out_err;
	}

	for (i = 0; i < vol->reserved_pebs; i++) {
		err = ubi_eba_unmap_leb(ubi, vol, i);
		if (err)
			goto out_err;
	}

	cdev_del(&vol->cdev);
	volume_sysfs_close(vol);

	spin_lock(&ubi->volumes_lock);
	ubi->rsvd_pebs -= reserved_pebs;
	ubi->avail_pebs += reserved_pebs;
	i = ubi->beb_rsvd_level - ubi->beb_rsvd_pebs;
	if (i > 0) {
		i = ubi->avail_pebs >= i ? i : ubi->avail_pebs;
		ubi->avail_pebs -= i;
		ubi->rsvd_pebs += i;
		ubi->beb_rsvd_pebs += i;
		if (i > 0)
			ubi_msg("reserve more %d PEBs", i);
	}
	ubi->vol_count -= 1;
	spin_unlock(&ubi->volumes_lock);

	ubi_volume_notify(ubi, vol, UBI_VOLUME_REMOVED);
	if (!no_vtbl && paranoid_check_volumes(ubi))
		dbg_err("check failed while removing volume %d", vol_id);

	return err;

out_err:
	ubi_err("cannot remove volume %d, error %d", vol_id, err);
	spin_lock(&ubi->volumes_lock);
	ubi->volumes[vol_id] = vol;
out_unlock:
	spin_unlock(&ubi->volumes_lock);
	return err;
}