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
struct ubi_volume {int vol_id; int* eba_tbl; int data_pad; } ;
struct ubi_vid_hdr {void* sqnum; void* data_pad; int /*<<< orphan*/  compat; void* lnum; void* vol_id; int /*<<< orphan*/  vol_type; } ;
struct ubi_device {scalar_t__ bad_allowed; scalar_t__ ro_mode; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EROFS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int UBI_IO_RETRIES ; 
 int /*<<< orphan*/  UBI_VID_DYNAMIC ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_eba (char*,int,int,int,int,int) ; 
 int leb_write_lock (struct ubi_device*,int,int) ; 
 int /*<<< orphan*/  leb_write_unlock (struct ubi_device*,int,int) ; 
 int /*<<< orphan*/  next_sqnum (struct ubi_device*) ; 
 int recover_peb (struct ubi_device*,int,int,int,void const*,int,int) ; 
 int /*<<< orphan*/  ubi_free_vid_hdr (struct ubi_device*,struct ubi_vid_hdr*) ; 
 int /*<<< orphan*/  ubi_get_compat (struct ubi_device*,int) ; 
 int ubi_io_write_data (struct ubi_device*,void const*,int,int,int) ; 
 int ubi_io_write_vid_hdr (struct ubi_device*,int,struct ubi_vid_hdr*) ; 
 int /*<<< orphan*/  ubi_msg (char*) ; 
 int /*<<< orphan*/  ubi_ro_mode (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_warn (char*,int,...) ; 
 int ubi_wl_get_peb (struct ubi_device*,int) ; 
 int ubi_wl_put_peb (struct ubi_device*,int,int) ; 
 struct ubi_vid_hdr* ubi_zalloc_vid_hdr (struct ubi_device*,int /*<<< orphan*/ ) ; 

int ubi_eba_write_leb(struct ubi_device *ubi, struct ubi_volume *vol, int lnum,
		      const void *buf, int offset, int len, int dtype)
{
	int err, pnum, tries = 0, vol_id = vol->vol_id;
	struct ubi_vid_hdr *vid_hdr;

	if (ubi->ro_mode)
		return -EROFS;

	err = leb_write_lock(ubi, vol_id, lnum);
	if (err)
		return err;

	pnum = vol->eba_tbl[lnum];
	if (pnum >= 0) {
		dbg_eba("write %d bytes at offset %d of LEB %d:%d, PEB %d",
			len, offset, vol_id, lnum, pnum);

		err = ubi_io_write_data(ubi, buf, pnum, offset, len);
		if (err) {
			ubi_warn("failed to write data to PEB %d", pnum);
			if (err == -EIO && ubi->bad_allowed)
				err = recover_peb(ubi, pnum, vol_id, lnum, buf,
						  offset, len);
			if (err)
				ubi_ro_mode(ubi);
		}
		leb_write_unlock(ubi, vol_id, lnum);
		return err;
	}

	/*
	 * The logical eraseblock is not mapped. We have to get a free physical
	 * eraseblock and write the volume identifier header there first.
	 */
	vid_hdr = ubi_zalloc_vid_hdr(ubi, GFP_NOFS);
	if (!vid_hdr) {
		leb_write_unlock(ubi, vol_id, lnum);
		return -ENOMEM;
	}

	vid_hdr->vol_type = UBI_VID_DYNAMIC;
	vid_hdr->sqnum = cpu_to_be64(next_sqnum(ubi));
	vid_hdr->vol_id = cpu_to_be32(vol_id);
	vid_hdr->lnum = cpu_to_be32(lnum);
	vid_hdr->compat = ubi_get_compat(ubi, vol_id);
	vid_hdr->data_pad = cpu_to_be32(vol->data_pad);

retry:
	pnum = ubi_wl_get_peb(ubi, dtype);
	if (pnum < 0) {
		ubi_free_vid_hdr(ubi, vid_hdr);
		leb_write_unlock(ubi, vol_id, lnum);
		return pnum;
	}

	dbg_eba("write VID hdr and %d bytes at offset %d of LEB %d:%d, PEB %d",
		len, offset, vol_id, lnum, pnum);

	err = ubi_io_write_vid_hdr(ubi, pnum, vid_hdr);
	if (err) {
		ubi_warn("failed to write VID header to LEB %d:%d, PEB %d",
			 vol_id, lnum, pnum);
		goto write_error;
	}

	if (len) {
		err = ubi_io_write_data(ubi, buf, pnum, offset, len);
		if (err) {
			ubi_warn("failed to write %d bytes at offset %d of "
				 "LEB %d:%d, PEB %d", len, offset, vol_id,
				 lnum, pnum);
			goto write_error;
		}
	}

	vol->eba_tbl[lnum] = pnum;

	leb_write_unlock(ubi, vol_id, lnum);
	ubi_free_vid_hdr(ubi, vid_hdr);
	return 0;

write_error:
	if (err != -EIO || !ubi->bad_allowed) {
		ubi_ro_mode(ubi);
		leb_write_unlock(ubi, vol_id, lnum);
		ubi_free_vid_hdr(ubi, vid_hdr);
		return err;
	}

	/*
	 * Fortunately, this is the first write operation to this physical
	 * eraseblock, so just put it and request a new one. We assume that if
	 * this physical eraseblock went bad, the erase code will handle that.
	 */
	err = ubi_wl_put_peb(ubi, pnum, 1);
	if (err || ++tries > UBI_IO_RETRIES) {
		ubi_ro_mode(ubi);
		leb_write_unlock(ubi, vol_id, lnum);
		ubi_free_vid_hdr(ubi, vid_hdr);
		return err;
	}

	vid_hdr->sqnum = cpu_to_be64(next_sqnum(ubi));
	ubi_msg("try another PEB");
	goto retry;
}