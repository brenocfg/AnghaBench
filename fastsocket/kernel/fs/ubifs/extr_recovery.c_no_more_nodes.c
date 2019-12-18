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
struct ubifs_info {int /*<<< orphan*/  min_io_size; } ;
struct ubifs_ch {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EUCLEAN ; 
 int UBIFS_CH_SZ ; 
 int /*<<< orphan*/  dbg_rcvry (char*,int,int) ; 
 scalar_t__ is_empty (void*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_check_node (struct ubifs_info const*,void*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int no_more_nodes(const struct ubifs_info *c, void *buf, int len,
			int lnum, int offs)
{
	struct ubifs_ch *ch = buf;
	int skip, dlen = le32_to_cpu(ch->len);

	/* Check for empty space after the corrupt node's common header */
	skip = ALIGN(offs + UBIFS_CH_SZ, c->min_io_size) - offs;
	if (is_empty(buf + skip, len - skip))
		return 1;
	/*
	 * The area after the common header size is not empty, so the common
	 * header must be intact. Check it.
	 */
	if (ubifs_check_node(c, buf, lnum, offs, 1, 0) != -EUCLEAN) {
		dbg_rcvry("unexpected bad common header at %d:%d", lnum, offs);
		return 0;
	}
	/* Now we know the corrupt node's length we can skip over it */
	skip = ALIGN(offs + dlen, c->min_io_size) - offs;
	/* After which there should be empty space */
	if (is_empty(buf + skip, len - skip))
		return 1;
	dbg_rcvry("unexpected data at %d:%d", lnum, offs + skip);
	return 0;
}