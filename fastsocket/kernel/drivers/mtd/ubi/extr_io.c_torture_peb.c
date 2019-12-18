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
struct ubi_device {int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  peb_size; int /*<<< orphan*/  peb_buf1; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EBADMSG ; 
 int EIO ; 
 int UBI_IO_BITFLIPS ; 
 int check_pattern (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int do_sync_erase (struct ubi_device*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* patterns ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_err (char*,int,...) ; 
 int ubi_io_read (struct ubi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ubi_io_write (struct ubi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_msg (char*,int) ; 

__attribute__((used)) static int torture_peb(struct ubi_device *ubi, int pnum)
{
	int err, i, patt_count;

	ubi_msg("run torture test for PEB %d", pnum);
	patt_count = ARRAY_SIZE(patterns);
	ubi_assert(patt_count > 0);

	mutex_lock(&ubi->buf_mutex);
	for (i = 0; i < patt_count; i++) {
		err = do_sync_erase(ubi, pnum);
		if (err)
			goto out;

		/* Make sure the PEB contains only 0xFF bytes */
		err = ubi_io_read(ubi, ubi->peb_buf1, pnum, 0, ubi->peb_size);
		if (err)
			goto out;

		err = check_pattern(ubi->peb_buf1, 0xFF, ubi->peb_size);
		if (err == 0) {
			ubi_err("erased PEB %d, but a non-0xFF byte found",
				pnum);
			err = -EIO;
			goto out;
		}

		/* Write a pattern and check it */
		memset(ubi->peb_buf1, patterns[i], ubi->peb_size);
		err = ubi_io_write(ubi, ubi->peb_buf1, pnum, 0, ubi->peb_size);
		if (err)
			goto out;

		memset(ubi->peb_buf1, ~patterns[i], ubi->peb_size);
		err = ubi_io_read(ubi, ubi->peb_buf1, pnum, 0, ubi->peb_size);
		if (err)
			goto out;

		err = check_pattern(ubi->peb_buf1, patterns[i], ubi->peb_size);
		if (err == 0) {
			ubi_err("pattern %x checking failed for PEB %d",
				patterns[i], pnum);
			err = -EIO;
			goto out;
		}
	}

	err = patt_count;
	ubi_msg("PEB %d passed torture test, do not mark it a bad", pnum);

out:
	mutex_unlock(&ubi->buf_mutex);
	if (err == UBI_IO_BITFLIPS || err == -EBADMSG) {
		/*
		 * If a bit-flip or data integrity error was detected, the test
		 * has not passed because it happened on a freshly erased
		 * physical eraseblock which means something is wrong with it.
		 */
		ubi_err("read problems on freshly erased PEB %d, must be bad",
			pnum);
		err = -EIO;
	}
	return err;
}