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
struct ubi_vtbl_record {int dummy; } ;
struct ubi_volume_desc {struct ubi_volume* vol; } ;
struct ubi_volume {int reserved_pebs; int /*<<< orphan*/  name; } ;
struct ubi_device {scalar_t__ avail_pebs; TYPE_1__* vtbl; struct ubi_volume** volumes; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBI_VTBL_AUTORESIZE_FLG ; 
 int /*<<< orphan*/  memcpy (struct ubi_vtbl_record*,TYPE_1__*,int) ; 
 int ubi_change_vtbl_record (struct ubi_device*,int,struct ubi_vtbl_record*) ; 
 int /*<<< orphan*/  ubi_err (char*,int) ; 
 int /*<<< orphan*/  ubi_msg (char*,int,int /*<<< orphan*/ ,int,int) ; 
 int ubi_resize_volume (struct ubi_volume_desc*,scalar_t__) ; 

__attribute__((used)) static int autoresize(struct ubi_device *ubi, int vol_id)
{
	struct ubi_volume_desc desc;
	struct ubi_volume *vol = ubi->volumes[vol_id];
	int err, old_reserved_pebs = vol->reserved_pebs;

	/*
	 * Clear the auto-resize flag in the volume in-memory copy of the
	 * volume table, and 'ubi_resize_volume()' will propagate this change
	 * to the flash.
	 */
	ubi->vtbl[vol_id].flags &= ~UBI_VTBL_AUTORESIZE_FLG;

	if (ubi->avail_pebs == 0) {
		struct ubi_vtbl_record vtbl_rec;

		/*
		 * No available PEBs to re-size the volume, clear the flag on
		 * flash and exit.
		 */
		memcpy(&vtbl_rec, &ubi->vtbl[vol_id],
		       sizeof(struct ubi_vtbl_record));
		err = ubi_change_vtbl_record(ubi, vol_id, &vtbl_rec);
		if (err)
			ubi_err("cannot clean auto-resize flag for volume %d",
				vol_id);
	} else {
		desc.vol = vol;
		err = ubi_resize_volume(&desc,
					old_reserved_pebs + ubi->avail_pebs);
		if (err)
			ubi_err("cannot auto-resize volume %d", vol_id);
	}

	if (err)
		return err;

	ubi_msg("volume %d (\"%s\") re-sized from %d to %d LEBs", vol_id,
		vol->name, old_reserved_pebs, vol->reserved_pebs);
	return 0;
}