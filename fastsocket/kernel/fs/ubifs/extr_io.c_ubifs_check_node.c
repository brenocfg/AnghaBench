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
typedef  scalar_t__ uint32_t ;
struct ubifs_info {int leb_cnt; int leb_size; scalar_t__ no_chk_data_crc; int /*<<< orphan*/  always_chk_crc; TYPE_1__* ranges; } ;
struct ubifs_ch {int node_type; int /*<<< orphan*/  crc; int /*<<< orphan*/  len; int /*<<< orphan*/  magic; } ;
struct TYPE_2__ {int max_len; int len; int min_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  UBIFS_CRC32_INIT ; 
 int UBIFS_DATA_NODE ; 
 scalar_t__ UBIFS_NODE_MAGIC ; 
 int UBIFS_NODE_TYPES_CNT ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  dbg_dump_node (struct ubifs_info const*,void const*) ; 
 int /*<<< orphan*/  dbg_dump_stack () ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_err (char*,int,...) ; 

int ubifs_check_node(const struct ubifs_info *c, const void *buf, int lnum,
		     int offs, int quiet, int must_chk_crc)
{
	int err = -EINVAL, type, node_len;
	uint32_t crc, node_crc, magic;
	const struct ubifs_ch *ch = buf;

	ubifs_assert(lnum >= 0 && lnum < c->leb_cnt && offs >= 0);
	ubifs_assert(!(offs & 7) && offs < c->leb_size);

	magic = le32_to_cpu(ch->magic);
	if (magic != UBIFS_NODE_MAGIC) {
		if (!quiet)
			ubifs_err("bad magic %#08x, expected %#08x",
				  magic, UBIFS_NODE_MAGIC);
		err = -EUCLEAN;
		goto out;
	}

	type = ch->node_type;
	if (type < 0 || type >= UBIFS_NODE_TYPES_CNT) {
		if (!quiet)
			ubifs_err("bad node type %d", type);
		goto out;
	}

	node_len = le32_to_cpu(ch->len);
	if (node_len + offs > c->leb_size)
		goto out_len;

	if (c->ranges[type].max_len == 0) {
		if (node_len != c->ranges[type].len)
			goto out_len;
	} else if (node_len < c->ranges[type].min_len ||
		   node_len > c->ranges[type].max_len)
		goto out_len;

	if (!must_chk_crc && type == UBIFS_DATA_NODE && !c->always_chk_crc &&
	     c->no_chk_data_crc)
		return 0;

	crc = crc32(UBIFS_CRC32_INIT, buf + 8, node_len - 8);
	node_crc = le32_to_cpu(ch->crc);
	if (crc != node_crc) {
		if (!quiet)
			ubifs_err("bad CRC: calculated %#08x, read %#08x",
				  crc, node_crc);
		err = -EUCLEAN;
		goto out;
	}

	return 0;

out_len:
	if (!quiet)
		ubifs_err("bad node length %d", node_len);
out:
	if (!quiet) {
		ubifs_err("bad node at LEB %d:%d", lnum, offs);
		dbg_dump_node(c, buf);
		dbg_dump_stack();
	}
	return err;
}