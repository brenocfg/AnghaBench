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
struct ubifs_scan_leb {int lnum; int ecc; void* buf; int /*<<< orphan*/  nodes; } ;
struct ubifs_info {scalar_t__ leb_size; int /*<<< orphan*/  ubi; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOMEM ; 
 struct ubifs_scan_leb* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_scan (char*,int,int) ; 
 int /*<<< orphan*/  kfree (struct ubifs_scan_leb*) ; 
 struct ubifs_scan_leb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ubi_read (int /*<<< orphan*/ ,int,void*,int,scalar_t__) ; 
 int /*<<< orphan*/  ubifs_err (char*,scalar_t__,int,int,int) ; 

struct ubifs_scan_leb *ubifs_start_scan(const struct ubifs_info *c, int lnum,
					int offs, void *sbuf)
{
	struct ubifs_scan_leb *sleb;
	int err;

	dbg_scan("scan LEB %d:%d", lnum, offs);

	sleb = kzalloc(sizeof(struct ubifs_scan_leb), GFP_NOFS);
	if (!sleb)
		return ERR_PTR(-ENOMEM);

	sleb->lnum = lnum;
	INIT_LIST_HEAD(&sleb->nodes);
	sleb->buf = sbuf;

	err = ubi_read(c->ubi, lnum, sbuf + offs, offs, c->leb_size - offs);
	if (err && err != -EBADMSG) {
		ubifs_err("cannot read %d bytes from LEB %d:%d,"
			  " error %d", c->leb_size - offs, lnum, offs, err);
		kfree(sleb);
		return ERR_PTR(err);
	}

	if (err == -EBADMSG)
		sleb->ecc = 1;

	return sleb;
}