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
struct ubi_volume {scalar_t__ vol_type; int reserved_pebs; scalar_t__* eba_tbl; scalar_t__ upd_marker; int /*<<< orphan*/  vol_id; struct ubi_device* ubi; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int EBADMSG ; 
 int EINVAL ; 
 int EROFS ; 
 int UBI_LONGTERM ; 
 scalar_t__ UBI_READONLY ; 
 int UBI_SHORTTERM ; 
 scalar_t__ UBI_STATIC_VOLUME ; 
 int UBI_UNKNOWN ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int) ; 
 int ubi_eba_write_leb (struct ubi_device*,struct ubi_volume*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ubi_leb_map(struct ubi_volume_desc *desc, int lnum, int dtype)
{
	struct ubi_volume *vol = desc->vol;
	struct ubi_device *ubi = vol->ubi;

	dbg_gen("unmap LEB %d:%d", vol->vol_id, lnum);

	if (desc->mode == UBI_READONLY || vol->vol_type == UBI_STATIC_VOLUME)
		return -EROFS;

	if (lnum < 0 || lnum >= vol->reserved_pebs)
		return -EINVAL;

	if (dtype != UBI_LONGTERM && dtype != UBI_SHORTTERM &&
	    dtype != UBI_UNKNOWN)
		return -EINVAL;

	if (vol->upd_marker)
		return -EBADF;

	if (vol->eba_tbl[lnum] >= 0)
		return -EBADMSG;

	return ubi_eba_write_leb(ubi, vol, lnum, NULL, 0, 0, dtype);
}