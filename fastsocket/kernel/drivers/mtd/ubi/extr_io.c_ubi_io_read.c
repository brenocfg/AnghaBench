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
struct ubi_device {int peb_count; int peb_size; TYPE_1__* mtd; } ;
typedef  int loff_t ;
struct TYPE_2__ {int (* read ) (TYPE_1__*,int,int,size_t*,void*) ;} ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int EIO ; 
 int EUCLEAN ; 
 int UBI_IO_BITFLIPS ; 
 int /*<<< orphan*/  UBI_IO_RETRIES ; 
 int /*<<< orphan*/  dbg_gen (char*) ; 
 int /*<<< orphan*/  dbg_io (char*,int,int,int,...) ; 
 int /*<<< orphan*/  dbg_msg (char*,int) ; 
 int paranoid_check_not_bad (struct ubi_device const*,int) ; 
 int stub1 (TYPE_1__*,int,int,size_t*,void*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_dbg_dump_stack () ; 
 scalar_t__ ubi_dbg_is_bitflip () ; 
 int /*<<< orphan*/  ubi_err (char*,int,int,int,int,size_t) ; 
 int /*<<< orphan*/  yield () ; 

int ubi_io_read(const struct ubi_device *ubi, void *buf, int pnum, int offset,
		int len)
{
	int err, retries = 0;
	size_t read;
	loff_t addr;

	dbg_io("read %d bytes from PEB %d:%d", len, pnum, offset);

	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);
	ubi_assert(offset >= 0 && offset + len <= ubi->peb_size);
	ubi_assert(len > 0);

	err = paranoid_check_not_bad(ubi, pnum);
	if (err)
		return err > 0 ? -EINVAL : err;

	addr = (loff_t)pnum * ubi->peb_size + offset;
retry:
	err = ubi->mtd->read(ubi->mtd, addr, len, &read, buf);
	if (err) {
		if (err == -EUCLEAN) {
			/*
			 * -EUCLEAN is reported if there was a bit-flip which
			 * was corrected, so this is harmless.
			 *
			 * We do not report about it here unless debugging is
			 * enabled. A corresponding message will be printed
			 * later, when it is has been scrubbed.
			 */
			dbg_msg("fixable bit-flip detected at PEB %d", pnum);
			ubi_assert(len == read);
			return UBI_IO_BITFLIPS;
		}

		if (read != len && retries++ < UBI_IO_RETRIES) {
			dbg_io("error %d while reading %d bytes from PEB %d:%d,"
			       " read only %zd bytes, retry",
			       err, len, pnum, offset, read);
			yield();
			goto retry;
		}

		ubi_err("error %d while reading %d bytes from PEB %d:%d, "
			"read %zd bytes", err, len, pnum, offset, read);
		ubi_dbg_dump_stack();

		/*
		 * The driver should never return -EBADMSG if it failed to read
		 * all the requested data. But some buggy drivers might do
		 * this, so we change it to -EIO.
		 */
		if (read != len && err == -EBADMSG) {
			ubi_assert(0);
			err = -EIO;
		}
	} else {
		ubi_assert(len == read);

		if (ubi_dbg_is_bitflip()) {
			dbg_gen("bit-flip (emulated)");
			err = UBI_IO_BITFLIPS;
		}
	}

	return err;
}