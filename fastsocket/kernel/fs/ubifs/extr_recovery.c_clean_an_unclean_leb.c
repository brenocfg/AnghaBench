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
struct ubifs_unclean_leb {int lnum; int endpt; } ;
struct ubifs_info {int min_io_size; int /*<<< orphan*/  ubi; int /*<<< orphan*/  sbuf; } ;
struct ubifs_ch {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EBADMSG ; 
 int EUCLEAN ; 
 int SCANNED_A_NODE ; 
 int SCANNED_EMPTY_SPACE ; 
 int /*<<< orphan*/  UBI_UNKNOWN ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dbg_rcvry (char*,int,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ubi_leb_change (int /*<<< orphan*/ ,int,void*,int,int /*<<< orphan*/ ) ; 
 int ubi_read (int /*<<< orphan*/ ,int,void*,int,int) ; 
 int /*<<< orphan*/  ubifs_err (char*,int,int) ; 
 int ubifs_leb_unmap (struct ubifs_info const*,int) ; 
 int /*<<< orphan*/  ubifs_pad (struct ubifs_info const*,void*,int) ; 
 int ubifs_scan_a_node (struct ubifs_info const*,void*,int,int,int,int) ; 
 int /*<<< orphan*/  ubifs_scanned_corruption (struct ubifs_info const*,int,int,void*) ; 

__attribute__((used)) static int clean_an_unclean_leb(const struct ubifs_info *c,
				struct ubifs_unclean_leb *ucleb, void *sbuf)
{
	int err, lnum = ucleb->lnum, offs = 0, len = ucleb->endpt, quiet = 1;
	void *buf = sbuf;

	dbg_rcvry("LEB %d len %d", lnum, len);

	if (len == 0) {
		/* Nothing to read, just unmap it */
		err = ubifs_leb_unmap(c, lnum);
		if (err)
			return err;
		return 0;
	}

	err = ubi_read(c->ubi, lnum, buf, offs, len);
	if (err && err != -EBADMSG)
		return err;

	while (len >= 8) {
		int ret;

		cond_resched();

		/* Scan quietly until there is an error */
		ret = ubifs_scan_a_node(c, buf, len, lnum, offs, quiet);

		if (ret == SCANNED_A_NODE) {
			/* A valid node, and not a padding node */
			struct ubifs_ch *ch = buf;
			int node_len;

			node_len = ALIGN(le32_to_cpu(ch->len), 8);
			offs += node_len;
			buf += node_len;
			len -= node_len;
			continue;
		}

		if (ret > 0) {
			/* Padding bytes or a valid padding node */
			offs += ret;
			buf += ret;
			len -= ret;
			continue;
		}

		if (ret == SCANNED_EMPTY_SPACE) {
			ubifs_err("unexpected empty space at %d:%d",
				  lnum, offs);
			return -EUCLEAN;
		}

		if (quiet) {
			/* Redo the last scan but noisily */
			quiet = 0;
			continue;
		}

		ubifs_scanned_corruption(c, lnum, offs, buf);
		return -EUCLEAN;
	}

	/* Pad to min_io_size */
	len = ALIGN(ucleb->endpt, c->min_io_size);
	if (len > ucleb->endpt) {
		int pad_len = len - ALIGN(ucleb->endpt, 8);

		if (pad_len > 0) {
			buf = c->sbuf + len - pad_len;
			ubifs_pad(c, buf, pad_len);
		}
	}

	/* Write back the LEB atomically */
	err = ubi_leb_change(c->ubi, lnum, sbuf, len, UBI_UNKNOWN);
	if (err)
		return err;

	dbg_rcvry("cleaned LEB %d", lnum);

	return 0;
}