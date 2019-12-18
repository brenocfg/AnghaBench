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
struct ubifs_info {int min_io_size; int leb_size; int /*<<< orphan*/  ubi; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBI_UNKNOWN ; 
 int /*<<< orphan*/  dbg_rcvry (char*,int,int) ; 
 int /*<<< orphan*/  is_empty (void*,int) ; 
 int ubi_leb_change (int /*<<< orphan*/ ,int,void*,int,int /*<<< orphan*/ ) ; 
 int ubi_read (int /*<<< orphan*/ ,int,void*,int,int) ; 
 int ubifs_leb_unmap (struct ubifs_info const*,int) ; 

__attribute__((used)) static int recover_head(const struct ubifs_info *c, int lnum, int offs,
			void *sbuf)
{
	int len, err;

	if (c->min_io_size > 1)
		len = c->min_io_size;
	else
		len = 512;
	if (offs + len > c->leb_size)
		len = c->leb_size - offs;

	if (!len)
		return 0;

	/* Read at the head location and check it is empty flash */
	err = ubi_read(c->ubi, lnum, sbuf, offs, len);
	if (err || !is_empty(sbuf, len)) {
		dbg_rcvry("cleaning head at %d:%d", lnum, offs);
		if (offs == 0)
			return ubifs_leb_unmap(c, lnum);
		err = ubi_read(c->ubi, lnum, sbuf, 0, offs);
		if (err)
			return err;
		return ubi_leb_change(c->ubi, lnum, sbuf, offs, UBI_UNKNOWN);
	}

	return 0;
}