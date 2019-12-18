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
struct ubifs_info {int lsave_cnt; int* lsave; int leb_cnt; int /*<<< orphan*/  lsave_sz; int /*<<< orphan*/  lsave_offs; int /*<<< orphan*/  lsave_lnum; int /*<<< orphan*/  ubi; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ubi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_lpt_lookup (struct ubifs_info*,int) ; 
 int unpack_lsave (struct ubifs_info*,void*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_lsave(struct ubifs_info *c)
{
	int err, i;
	void *buf;

	buf = vmalloc(c->lsave_sz);
	if (!buf)
		return -ENOMEM;
	err = ubi_read(c->ubi, c->lsave_lnum, buf, c->lsave_offs, c->lsave_sz);
	if (err)
		goto out;
	err = unpack_lsave(c, buf);
	if (err)
		goto out;
	for (i = 0; i < c->lsave_cnt; i++) {
		int lnum = c->lsave[i];

		/*
		 * Due to automatic resizing, the values in the lsave table
		 * could be beyond the volume size - just ignore them.
		 */
		if (lnum >= c->leb_cnt)
			continue;
		ubifs_lpt_lookup(c, lnum);
	}
out:
	vfree(buf);
	return err;
}