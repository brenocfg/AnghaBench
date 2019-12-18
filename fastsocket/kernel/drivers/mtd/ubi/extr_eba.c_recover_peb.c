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
struct ubi_volume {int* eba_tbl; } ;
struct ubi_vid_hdr {int /*<<< orphan*/  sqnum; } ;
struct ubi_device {int /*<<< orphan*/  buf_mutex; scalar_t__ peb_buf1; struct ubi_volume** volumes; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int UBI_IO_BITFLIPS ; 
 int UBI_IO_RETRIES ; 
 int /*<<< orphan*/  UBI_UNKNOWN ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_sqnum (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_free_vid_hdr (struct ubi_device*,struct ubi_vid_hdr*) ; 
 int ubi_io_read_data (struct ubi_device*,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int ubi_io_read_vid_hdr (struct ubi_device*,int,struct ubi_vid_hdr*,int) ; 
 int ubi_io_write_data (struct ubi_device*,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int ubi_io_write_vid_hdr (struct ubi_device*,int,struct ubi_vid_hdr*) ; 
 int /*<<< orphan*/  ubi_msg (char*,...) ; 
 int /*<<< orphan*/  ubi_warn (char*,int) ; 
 int ubi_wl_get_peb (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_wl_put_peb (struct ubi_device*,int,int) ; 
 struct ubi_vid_hdr* ubi_zalloc_vid_hdr (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int vol_id2idx (struct ubi_device*,int) ; 

__attribute__((used)) static int recover_peb(struct ubi_device *ubi, int pnum, int vol_id, int lnum,
		       const void *buf, int offset, int len)
{
	int err, idx = vol_id2idx(ubi, vol_id), new_pnum, data_size, tries = 0;
	struct ubi_volume *vol = ubi->volumes[idx];
	struct ubi_vid_hdr *vid_hdr;

	vid_hdr = ubi_zalloc_vid_hdr(ubi, GFP_NOFS);
	if (!vid_hdr)
		return -ENOMEM;

retry:
	new_pnum = ubi_wl_get_peb(ubi, UBI_UNKNOWN);
	if (new_pnum < 0) {
		ubi_free_vid_hdr(ubi, vid_hdr);
		return new_pnum;
	}

	ubi_msg("recover PEB %d, move data to PEB %d", pnum, new_pnum);

	err = ubi_io_read_vid_hdr(ubi, pnum, vid_hdr, 1);
	if (err && err != UBI_IO_BITFLIPS) {
		if (err > 0)
			err = -EIO;
		goto out_put;
	}

	vid_hdr->sqnum = cpu_to_be64(next_sqnum(ubi));
	err = ubi_io_write_vid_hdr(ubi, new_pnum, vid_hdr);
	if (err)
		goto write_error;

	data_size = offset + len;
	mutex_lock(&ubi->buf_mutex);
	memset(ubi->peb_buf1 + offset, 0xFF, len);

	/* Read everything before the area where the write failure happened */
	if (offset > 0) {
		err = ubi_io_read_data(ubi, ubi->peb_buf1, pnum, 0, offset);
		if (err && err != UBI_IO_BITFLIPS)
			goto out_unlock;
	}

	memcpy(ubi->peb_buf1 + offset, buf, len);

	err = ubi_io_write_data(ubi, ubi->peb_buf1, new_pnum, 0, data_size);
	if (err) {
		mutex_unlock(&ubi->buf_mutex);
		goto write_error;
	}

	mutex_unlock(&ubi->buf_mutex);
	ubi_free_vid_hdr(ubi, vid_hdr);

	vol->eba_tbl[lnum] = new_pnum;
	ubi_wl_put_peb(ubi, pnum, 1);

	ubi_msg("data was successfully recovered");
	return 0;

out_unlock:
	mutex_unlock(&ubi->buf_mutex);
out_put:
	ubi_wl_put_peb(ubi, new_pnum, 1);
	ubi_free_vid_hdr(ubi, vid_hdr);
	return err;

write_error:
	/*
	 * Bad luck? This physical eraseblock is bad too? Crud. Let's try to
	 * get another one.
	 */
	ubi_warn("failed to write to PEB %d", new_pnum);
	ubi_wl_put_peb(ubi, new_pnum, 1);
	if (++tries > UBI_IO_RETRIES) {
		ubi_free_vid_hdr(ubi, vid_hdr);
		return err;
	}
	ubi_msg("try again");
	goto retry;
}