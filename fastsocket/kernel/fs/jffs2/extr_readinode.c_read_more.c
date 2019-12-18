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
struct jffs2_sb_info {int wbuf_pagesize; } ;
struct jffs2_raw_node_ref {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  JFFS2_ERROR (char*,int,size_t,int) ; 
 int /*<<< orphan*/  dbg_readinode (char*,int) ; 
 int jffs2_flash_read (struct jffs2_sb_info*,int,int,size_t*,unsigned char*) ; 
 scalar_t__ jffs2_is_writebuffered (struct jffs2_sb_info*) ; 
 int ref_offset (struct jffs2_raw_node_ref*) ; 

__attribute__((used)) static int read_more(struct jffs2_sb_info *c, struct jffs2_raw_node_ref *ref,
		     int needed_len, int *rdlen, unsigned char *buf)
{
	int err, to_read = needed_len - *rdlen;
	size_t retlen;
	uint32_t offs;

	if (jffs2_is_writebuffered(c)) {
		int rem = to_read % c->wbuf_pagesize;

		if (rem)
			to_read += c->wbuf_pagesize - rem;
	}

	/* We need to read more data */
	offs = ref_offset(ref) + *rdlen;

	dbg_readinode("read more %d bytes\n", to_read);

	err = jffs2_flash_read(c, offs, to_read, &retlen, buf + *rdlen);
	if (err) {
		JFFS2_ERROR("can not read %d bytes from 0x%08x, "
			"error code: %d.\n", to_read, offs, err);
		return err;
	}

	if (retlen < to_read) {
		JFFS2_ERROR("short read at %#08x: %zu instead of %d.\n",
				offs, retlen, to_read);
		return -EIO;
	}

	*rdlen += to_read;
	return 0;
}