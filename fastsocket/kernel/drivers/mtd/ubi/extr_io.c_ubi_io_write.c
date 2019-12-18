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
struct ubi_device {int peb_count; int peb_size; int hdrs_min_io_size; int leb_start; TYPE_1__* mtd; scalar_t__ ro_mode; } ;
typedef  int loff_t ;
struct TYPE_2__ {int (* write ) (TYPE_1__*,int,int,size_t*,void const*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EROFS ; 
 int /*<<< orphan*/  dbg_err (char*,int,int,int) ; 
 int /*<<< orphan*/  dbg_io (char*,int,int,int) ; 
 int paranoid_check_not_bad (struct ubi_device*,int) ; 
 int paranoid_check_peb_ec_hdr (struct ubi_device*,int) ; 
 int paranoid_check_peb_vid_hdr (struct ubi_device*,int) ; 
 int stub1 (TYPE_1__*,int,int,size_t*,void const*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int ubi_dbg_check_all_ff (struct ubi_device*,int,int,int) ; 
 int /*<<< orphan*/  ubi_dbg_dump_flash (struct ubi_device*,int,int,int) ; 
 int /*<<< orphan*/  ubi_dbg_dump_stack () ; 
 scalar_t__ ubi_dbg_is_write_failure () ; 
 int /*<<< orphan*/  ubi_err (char*,...) ; 

int ubi_io_write(struct ubi_device *ubi, const void *buf, int pnum, int offset,
		 int len)
{
	int err;
	size_t written;
	loff_t addr;

	dbg_io("write %d bytes to PEB %d:%d", len, pnum, offset);

	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);
	ubi_assert(offset >= 0 && offset + len <= ubi->peb_size);
	ubi_assert(offset % ubi->hdrs_min_io_size == 0);
	ubi_assert(len > 0 && len % ubi->hdrs_min_io_size == 0);

	if (ubi->ro_mode) {
		ubi_err("read-only mode");
		return -EROFS;
	}

	/* The below has to be compiled out if paranoid checks are disabled */

	err = paranoid_check_not_bad(ubi, pnum);
	if (err)
		return err > 0 ? -EINVAL : err;

	/* The area we are writing to has to contain all 0xFF bytes */
	err = ubi_dbg_check_all_ff(ubi, pnum, offset, len);
	if (err)
		return err > 0 ? -EINVAL : err;

	if (offset >= ubi->leb_start) {
		/*
		 * We write to the data area of the physical eraseblock. Make
		 * sure it has valid EC and VID headers.
		 */
		err = paranoid_check_peb_ec_hdr(ubi, pnum);
		if (err)
			return err > 0 ? -EINVAL : err;
		err = paranoid_check_peb_vid_hdr(ubi, pnum);
		if (err)
			return err > 0 ? -EINVAL : err;
	}

	if (ubi_dbg_is_write_failure()) {
		dbg_err("cannot write %d bytes to PEB %d:%d "
			"(emulated)", len, pnum, offset);
		ubi_dbg_dump_stack();
		return -EIO;
	}

	addr = (loff_t)pnum * ubi->peb_size + offset;
	err = ubi->mtd->write(ubi->mtd, addr, len, &written, buf);
	if (err) {
		ubi_err("error %d while writing %d bytes to PEB %d:%d, written "
			"%zd bytes", err, len, pnum, offset, written);
		ubi_dbg_dump_stack();
		ubi_dbg_dump_flash(ubi, pnum, offset, len);
	} else
		ubi_assert(written == len);

	return err;
}