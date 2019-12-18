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
struct ubifs_wbuf {int lnum; int offs; int buf; int /*<<< orphan*/  lock; int /*<<< orphan*/  jhead; struct ubifs_info* c; } ;
struct ubifs_info {int leb_cnt; int leb_size; int /*<<< orphan*/  ubi; } ;
struct ubifs_ch {int node_type; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int UBIFS_NODE_TYPES_CNT ; 
 int /*<<< orphan*/  dbg_dump_node (struct ubifs_info const*,void*) ; 
 int /*<<< orphan*/  dbg_dump_stack () ; 
 int /*<<< orphan*/  dbg_io (char*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_jhead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_ntype (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ubi_read (int /*<<< orphan*/ ,int,void*,int,int) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int ubifs_check_node (struct ubifs_info const*,void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_err (char*,int,...) ; 
 int ubifs_read_node (struct ubifs_info const*,void*,int,int,int,int) ; 

int ubifs_read_node_wbuf(struct ubifs_wbuf *wbuf, void *buf, int type, int len,
			 int lnum, int offs)
{
	const struct ubifs_info *c = wbuf->c;
	int err, rlen, overlap;
	struct ubifs_ch *ch = buf;

	dbg_io("LEB %d:%d, %s, length %d, jhead %s", lnum, offs,
	       dbg_ntype(type), len, dbg_jhead(wbuf->jhead));
	ubifs_assert(wbuf && lnum >= 0 && lnum < c->leb_cnt && offs >= 0);
	ubifs_assert(!(offs & 7) && offs < c->leb_size);
	ubifs_assert(type >= 0 && type < UBIFS_NODE_TYPES_CNT);

	spin_lock(&wbuf->lock);
	overlap = (lnum == wbuf->lnum && offs + len > wbuf->offs);
	if (!overlap) {
		/* We may safely unlock the write-buffer and read the data */
		spin_unlock(&wbuf->lock);
		return ubifs_read_node(c, buf, type, len, lnum, offs);
	}

	/* Don't read under wbuf */
	rlen = wbuf->offs - offs;
	if (rlen < 0)
		rlen = 0;

	/* Copy the rest from the write-buffer */
	memcpy(buf + rlen, wbuf->buf + offs + rlen - wbuf->offs, len - rlen);
	spin_unlock(&wbuf->lock);

	if (rlen > 0) {
		/* Read everything that goes before write-buffer */
		err = ubi_read(c->ubi, lnum, buf, offs, rlen);
		if (err && err != -EBADMSG) {
			ubifs_err("failed to read node %d from LEB %d:%d, "
				  "error %d", type, lnum, offs, err);
			dbg_dump_stack();
			return err;
		}
	}

	if (type != ch->node_type) {
		ubifs_err("bad node type (%d but expected %d)",
			  ch->node_type, type);
		goto out;
	}

	err = ubifs_check_node(c, buf, lnum, offs, 0, 0);
	if (err) {
		ubifs_err("expected node type %d", type);
		return err;
	}

	rlen = le32_to_cpu(ch->len);
	if (rlen != len) {
		ubifs_err("bad node length %d, expected %d", rlen, len);
		goto out;
	}

	return 0;

out:
	ubifs_err("bad node at LEB %d:%d", lnum, offs);
	dbg_dump_node(c, buf);
	dbg_dump_stack();
	return -EINVAL;
}