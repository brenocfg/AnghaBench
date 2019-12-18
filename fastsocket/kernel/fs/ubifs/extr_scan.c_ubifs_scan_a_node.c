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
struct ubifs_pad_node {int /*<<< orphan*/  pad_len; } ;
struct ubifs_info {int leb_size; } ;
struct ubifs_ch {scalar_t__ node_type; int /*<<< orphan*/  len; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int SCANNED_A_BAD_PAD_NODE ; 
 int SCANNED_A_CORRUPT_NODE ; 
 int SCANNED_A_NODE ; 
 int SCANNED_EMPTY_SPACE ; 
 int SCANNED_GARBAGE ; 
 int UBIFS_CH_SZ ; 
 int UBIFS_NODE_MAGIC ; 
 scalar_t__ UBIFS_PAD_NODE ; 
 int /*<<< orphan*/  dbg_dump_node (struct ubifs_info const*,struct ubifs_pad_node*) ; 
 int /*<<< orphan*/  dbg_err (char*,int,int) ; 
 int /*<<< orphan*/  dbg_ntype (scalar_t__) ; 
 int /*<<< orphan*/  dbg_scan (char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int scan_padding_bytes (void*,int) ; 
 scalar_t__ ubifs_check_node (struct ubifs_info const*,void*,int,int,int,int) ; 
 int /*<<< orphan*/  ubifs_err (char*,int,int) ; 

int ubifs_scan_a_node(const struct ubifs_info *c, void *buf, int len, int lnum,
		      int offs, int quiet)
{
	struct ubifs_ch *ch = buf;
	uint32_t magic;

	magic = le32_to_cpu(ch->magic);

	if (magic == 0xFFFFFFFF) {
		dbg_scan("hit empty space");
		return SCANNED_EMPTY_SPACE;
	}

	if (magic != UBIFS_NODE_MAGIC)
		return scan_padding_bytes(buf, len);

	if (len < UBIFS_CH_SZ)
		return SCANNED_GARBAGE;

	dbg_scan("scanning %s", dbg_ntype(ch->node_type));

	if (ubifs_check_node(c, buf, lnum, offs, quiet, 1))
		return SCANNED_A_CORRUPT_NODE;

	if (ch->node_type == UBIFS_PAD_NODE) {
		struct ubifs_pad_node *pad = buf;
		int pad_len = le32_to_cpu(pad->pad_len);
		int node_len = le32_to_cpu(ch->len);

		/* Validate the padding node */
		if (pad_len < 0 ||
		    offs + node_len + pad_len > c->leb_size) {
			if (!quiet) {
				ubifs_err("bad pad node at LEB %d:%d",
					  lnum, offs);
				dbg_dump_node(c, pad);
			}
			return SCANNED_A_BAD_PAD_NODE;
		}

		/* Make the node pads to 8-byte boundary */
		if ((node_len + pad_len) & 7) {
			if (!quiet)
				dbg_err("bad padding length %d - %d",
					offs, offs + node_len + pad_len);
			return SCANNED_A_BAD_PAD_NODE;
		}

		dbg_scan("%d bytes padded, offset now %d",
			 pad_len, ALIGN(offs + node_len + pad_len, 8));

		return node_len + pad_len;
	}

	return SCANNED_A_NODE;
}