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
typedef  int uint32_t ;
struct ubi_volume {int* eba_tbl; } ;
struct ubi_vid_hdr {scalar_t__ vol_type; int copy_flag; int /*<<< orphan*/  sqnum; void* data_crc; void* data_size; void* data_pad; void* lnum; void* vol_id; } ;
struct ubi_device {int leb_size; int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  peb_buf2; int /*<<< orphan*/  peb_buf1; int /*<<< orphan*/  volumes_lock; struct ubi_volume** volumes; int /*<<< orphan*/  min_io_size; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int MOVE_CANCEL_BITFLIPS ; 
 int MOVE_CANCEL_RACE ; 
 int MOVE_SOURCE_RD_ERR ; 
 int MOVE_TARGET_RD_ERR ; 
 int MOVE_TARGET_WR_ERR ; 
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int UBI_IO_BITFLIPS ; 
 scalar_t__ UBI_VID_DYNAMIC ; 
 scalar_t__ UBI_VID_STATIC ; 
 int be32_to_cpu (void*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbg_wl (char*,int,...) ; 
 scalar_t__ is_error_sane (int) ; 
 int leb_write_trylock (struct ubi_device*,int,int) ; 
 int /*<<< orphan*/  leb_write_unlock (struct ubi_device*,int,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_sqnum (struct ubi_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int ubi_calc_data_len (struct ubi_device*,int /*<<< orphan*/ ,int) ; 
 int ubi_io_read_data (struct ubi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int ubi_io_read_vid_hdr (struct ubi_device*,int,struct ubi_vid_hdr*,int) ; 
 int ubi_io_write_data (struct ubi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int ubi_io_write_vid_hdr (struct ubi_device*,int,struct ubi_vid_hdr*) ; 
 int /*<<< orphan*/  ubi_warn (char*,int,...) ; 
 int vol_id2idx (struct ubi_device*,int) ; 

int ubi_eba_copy_leb(struct ubi_device *ubi, int from, int to,
		     struct ubi_vid_hdr *vid_hdr)
{
	int err, vol_id, lnum, data_size, aldata_size, idx;
	struct ubi_volume *vol;
	uint32_t crc;

	vol_id = be32_to_cpu(vid_hdr->vol_id);
	lnum = be32_to_cpu(vid_hdr->lnum);

	dbg_wl("copy LEB %d:%d, PEB %d to PEB %d", vol_id, lnum, from, to);

	if (vid_hdr->vol_type == UBI_VID_STATIC) {
		data_size = be32_to_cpu(vid_hdr->data_size);
		aldata_size = ALIGN(data_size, ubi->min_io_size);
	} else
		data_size = aldata_size =
			    ubi->leb_size - be32_to_cpu(vid_hdr->data_pad);

	idx = vol_id2idx(ubi, vol_id);
	spin_lock(&ubi->volumes_lock);
	/*
	 * Note, we may race with volume deletion, which means that the volume
	 * this logical eraseblock belongs to might be being deleted. Since the
	 * volume deletion un-maps all the volume's logical eraseblocks, it will
	 * be locked in 'ubi_wl_put_peb()' and wait for the WL worker to finish.
	 */
	vol = ubi->volumes[idx];
	spin_unlock(&ubi->volumes_lock);
	if (!vol) {
		/* No need to do further work, cancel */
		dbg_wl("volume %d is being removed, cancel", vol_id);
		return MOVE_CANCEL_RACE;
	}

	/*
	 * We do not want anybody to write to this logical eraseblock while we
	 * are moving it, so lock it.
	 *
	 * Note, we are using non-waiting locking here, because we cannot sleep
	 * on the LEB, since it may cause deadlocks. Indeed, imagine a task is
	 * unmapping the LEB which is mapped to the PEB we are going to move
	 * (@from). This task locks the LEB and goes sleep in the
	 * 'ubi_wl_put_peb()' function on the @ubi->move_mutex. In turn, we are
	 * holding @ubi->move_mutex and go sleep on the LEB lock. So, if the
	 * LEB is already locked, we just do not move it and return
	 * %MOVE_CANCEL_RACE, which means that UBI will re-try, but later.
	 */
	err = leb_write_trylock(ubi, vol_id, lnum);
	if (err) {
		dbg_wl("contention on LEB %d:%d, cancel", vol_id, lnum);
		return MOVE_CANCEL_RACE;
	}

	/*
	 * The LEB might have been put meanwhile, and the task which put it is
	 * probably waiting on @ubi->move_mutex. No need to continue the work,
	 * cancel it.
	 */
	if (vol->eba_tbl[lnum] != from) {
		dbg_wl("LEB %d:%d is no longer mapped to PEB %d, mapped to "
		       "PEB %d, cancel", vol_id, lnum, from,
		       vol->eba_tbl[lnum]);
		err = MOVE_CANCEL_RACE;
		goto out_unlock_leb;
	}

	/*
	 * OK, now the LEB is locked and we can safely start moving it. Since
	 * this function utilizes the @ubi->peb_buf1 buffer which is shared
	 * with some other functions - we lock the buffer by taking the
	 * @ubi->buf_mutex.
	 */
	mutex_lock(&ubi->buf_mutex);
	dbg_wl("read %d bytes of data", aldata_size);
	err = ubi_io_read_data(ubi, ubi->peb_buf1, from, 0, aldata_size);
	if (err && err != UBI_IO_BITFLIPS) {
		ubi_warn("error %d while reading data from PEB %d",
			 err, from);
		err = MOVE_SOURCE_RD_ERR;
		goto out_unlock_buf;
	}

	/*
	 * Now we have got to calculate how much data we have to copy. In
	 * case of a static volume it is fairly easy - the VID header contains
	 * the data size. In case of a dynamic volume it is more difficult - we
	 * have to read the contents, cut 0xFF bytes from the end and copy only
	 * the first part. We must do this to avoid writing 0xFF bytes as it
	 * may have some side-effects. And not only this. It is important not
	 * to include those 0xFFs to CRC because later the they may be filled
	 * by data.
	 */
	if (vid_hdr->vol_type == UBI_VID_DYNAMIC)
		aldata_size = data_size =
			ubi_calc_data_len(ubi, ubi->peb_buf1, data_size);

	cond_resched();
	crc = crc32(UBI_CRC32_INIT, ubi->peb_buf1, data_size);
	cond_resched();

	/*
	 * It may turn out to be that the whole @from physical eraseblock
	 * contains only 0xFF bytes. Then we have to only write the VID header
	 * and do not write any data. This also means we should not set
	 * @vid_hdr->copy_flag, @vid_hdr->data_size, and @vid_hdr->data_crc.
	 */
	if (data_size > 0) {
		vid_hdr->copy_flag = 1;
		vid_hdr->data_size = cpu_to_be32(data_size);
		vid_hdr->data_crc = cpu_to_be32(crc);
	}
	vid_hdr->sqnum = cpu_to_be64(next_sqnum(ubi));

	err = ubi_io_write_vid_hdr(ubi, to, vid_hdr);
	if (err) {
		if (err == -EIO)
			err = MOVE_TARGET_WR_ERR;
		goto out_unlock_buf;
	}

	cond_resched();

	/* Read the VID header back and check if it was written correctly */
	err = ubi_io_read_vid_hdr(ubi, to, vid_hdr, 1);
	if (err) {
		if (err != UBI_IO_BITFLIPS) {
			ubi_warn("error %d while reading VID header back from "
				  "PEB %d", err, to);
			if (is_error_sane(err))
				err = MOVE_TARGET_RD_ERR;
		} else
			err = MOVE_CANCEL_BITFLIPS;
		goto out_unlock_buf;
	}

	if (data_size > 0) {
		err = ubi_io_write_data(ubi, ubi->peb_buf1, to, 0, aldata_size);
		if (err) {
			if (err == -EIO)
				err = MOVE_TARGET_WR_ERR;
			goto out_unlock_buf;
		}

		cond_resched();

		/*
		 * We've written the data and are going to read it back to make
		 * sure it was written correctly.
		 */

		err = ubi_io_read_data(ubi, ubi->peb_buf2, to, 0, aldata_size);
		if (err) {
			if (err != UBI_IO_BITFLIPS) {
				ubi_warn("error %d while reading data back "
					 "from PEB %d", err, to);
				if (is_error_sane(err))
					err = MOVE_TARGET_RD_ERR;
			} else
				err = MOVE_CANCEL_BITFLIPS;
			goto out_unlock_buf;
		}

		cond_resched();

		if (memcmp(ubi->peb_buf1, ubi->peb_buf2, aldata_size)) {
			ubi_warn("read data back from PEB %d and it is "
				 "different", to);
			err = -EINVAL;
			goto out_unlock_buf;
		}
	}

	ubi_assert(vol->eba_tbl[lnum] == from);
	vol->eba_tbl[lnum] = to;

out_unlock_buf:
	mutex_unlock(&ubi->buf_mutex);
out_unlock_leb:
	leb_write_unlock(ubi, vol_id, lnum);
	return err;
}