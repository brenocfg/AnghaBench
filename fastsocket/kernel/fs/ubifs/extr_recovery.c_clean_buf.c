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
struct ubifs_info {scalar_t__ leb_size; int /*<<< orphan*/  min_io_size; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_rcvry (char*,int,int) ; 
 int /*<<< orphan*/  memset (void*,int,scalar_t__) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_pad (struct ubifs_info const*,void*,int) ; 

__attribute__((used)) static void clean_buf(const struct ubifs_info *c, void **buf, int lnum,
		      int *offs, int *len)
{
	int empty_offs, pad_len;

	lnum = lnum;
	dbg_rcvry("cleaning corruption at %d:%d", lnum, *offs);

	ubifs_assert(!(*offs & 7));
	empty_offs = ALIGN(*offs, c->min_io_size);
	pad_len = empty_offs - *offs;
	ubifs_pad(c, *buf, pad_len);
	*offs += pad_len;
	*buf += pad_len;
	*len -= pad_len;
	memset(*buf, 0xff, c->leb_size - empty_offs);
}