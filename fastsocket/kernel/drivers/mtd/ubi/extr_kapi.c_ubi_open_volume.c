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
struct ubi_volume_desc {int mode; struct ubi_volume* vol; } ;
struct ubi_volume {int exclusive; int readers; int writers; int ref_count; int checked; int corrupted; int /*<<< orphan*/  dev; } ;
struct ubi_device {int vtbl_slots; int /*<<< orphan*/  volumes_lock; int /*<<< orphan*/  ckvol_mutex; int /*<<< orphan*/  ubi_num; struct ubi_volume** volumes; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct ubi_volume_desc* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
#define  UBI_EXCLUSIVE 130 
 int UBI_MAX_DEVICES ; 
#define  UBI_READONLY 129 
#define  UBI_READWRITE 128 
 int /*<<< orphan*/  dbg_err (char*,int,int,int) ; 
 int /*<<< orphan*/  dbg_gen (char*,int,int,int) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ubi_volume_desc*) ; 
 struct ubi_volume_desc* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int ubi_check_volume (struct ubi_device*,int) ; 
 int /*<<< orphan*/  ubi_close_volume (struct ubi_volume_desc*) ; 
 struct ubi_device* ubi_get_device (int) ; 
 int /*<<< orphan*/  ubi_put_device (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_warn (char*,int,int /*<<< orphan*/ ) ; 

struct ubi_volume_desc *ubi_open_volume(int ubi_num, int vol_id, int mode)
{
	int err;
	struct ubi_volume_desc *desc;
	struct ubi_device *ubi;
	struct ubi_volume *vol;

	dbg_gen("open device %d, volume %d, mode %d", ubi_num, vol_id, mode);

	if (ubi_num < 0 || ubi_num >= UBI_MAX_DEVICES)
		return ERR_PTR(-EINVAL);

	if (mode != UBI_READONLY && mode != UBI_READWRITE &&
	    mode != UBI_EXCLUSIVE)
		return ERR_PTR(-EINVAL);

	/*
	 * First of all, we have to get the UBI device to prevent its removal.
	 */
	ubi = ubi_get_device(ubi_num);
	if (!ubi)
		return ERR_PTR(-ENODEV);

	if (vol_id < 0 || vol_id >= ubi->vtbl_slots) {
		err = -EINVAL;
		goto out_put_ubi;
	}

	desc = kmalloc(sizeof(struct ubi_volume_desc), GFP_KERNEL);
	if (!desc) {
		err = -ENOMEM;
		goto out_put_ubi;
	}

	err = -ENODEV;
	if (!try_module_get(THIS_MODULE))
		goto out_free;

	spin_lock(&ubi->volumes_lock);
	vol = ubi->volumes[vol_id];
	if (!vol)
		goto out_unlock;

	err = -EBUSY;
	switch (mode) {
	case UBI_READONLY:
		if (vol->exclusive)
			goto out_unlock;
		vol->readers += 1;
		break;

	case UBI_READWRITE:
		if (vol->exclusive || vol->writers > 0)
			goto out_unlock;
		vol->writers += 1;
		break;

	case UBI_EXCLUSIVE:
		if (vol->exclusive || vol->writers || vol->readers)
			goto out_unlock;
		vol->exclusive = 1;
		break;
	}
	get_device(&vol->dev);
	vol->ref_count += 1;
	spin_unlock(&ubi->volumes_lock);

	desc->vol = vol;
	desc->mode = mode;

	mutex_lock(&ubi->ckvol_mutex);
	if (!vol->checked) {
		/* This is the first open - check the volume */
		err = ubi_check_volume(ubi, vol_id);
		if (err < 0) {
			mutex_unlock(&ubi->ckvol_mutex);
			ubi_close_volume(desc);
			return ERR_PTR(err);
		}
		if (err == 1) {
			ubi_warn("volume %d on UBI device %d is corrupted",
				 vol_id, ubi->ubi_num);
			vol->corrupted = 1;
		}
		vol->checked = 1;
	}
	mutex_unlock(&ubi->ckvol_mutex);

	return desc;

out_unlock:
	spin_unlock(&ubi->volumes_lock);
	module_put(THIS_MODULE);
out_free:
	kfree(desc);
out_put_ubi:
	ubi_put_device(ubi);
	dbg_err("cannot open device %d, volume %d, error %d",
		ubi_num, vol_id, err);
	return ERR_PTR(err);
}