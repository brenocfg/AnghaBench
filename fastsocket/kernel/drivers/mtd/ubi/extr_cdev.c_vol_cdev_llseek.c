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
struct ubi_volume_desc {struct ubi_volume* vol; } ;
struct ubi_volume {scalar_t__ used_bytes; int /*<<< orphan*/  vol_id; scalar_t__ updating; } ;
struct file {scalar_t__ f_pos; struct ubi_volume_desc* private_data; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  dbg_err (char*,...) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static loff_t vol_cdev_llseek(struct file *file, loff_t offset, int origin)
{
	struct ubi_volume_desc *desc = file->private_data;
	struct ubi_volume *vol = desc->vol;
	loff_t new_offset;

	if (vol->updating) {
		 /* Update is in progress, seeking is prohibited */
		dbg_err("updating");
		return -EBUSY;
	}

	switch (origin) {
	case 0: /* SEEK_SET */
		new_offset = offset;
		break;
	case 1: /* SEEK_CUR */
		new_offset = file->f_pos + offset;
		break;
	case 2: /* SEEK_END */
		new_offset = vol->used_bytes + offset;
		break;
	default:
		return -EINVAL;
	}

	if (new_offset < 0 || new_offset > vol->used_bytes) {
		dbg_err("bad seek %lld", new_offset);
		return -EINVAL;
	}

	dbg_gen("seek volume %d, offset %lld, origin %d, new offset %lld",
		vol->vol_id, offset, origin, new_offset);

	file->f_pos = new_offset;
	return new_offset;
}