#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_inode {int flags; int compr_type; } ;
struct ubifs_info {TYPE_2__* jheads; } ;
struct TYPE_3__ {int /*<<< orphan*/  node_type; } ;
struct ubifs_data_node {int /*<<< orphan*/  compr_type; int /*<<< orphan*/  data; int /*<<< orphan*/  size; int /*<<< orphan*/  key; TYPE_1__ ch; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  wbuf; } ;

/* Variables and functions */
 size_t DATAHD ; 
 int /*<<< orphan*/  DBGKEY (union ubifs_key const*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int UBIFS_BLOCK_SIZE ; 
 int UBIFS_COMPR_FL ; 
 int UBIFS_COMPR_NONE ; 
 int /*<<< orphan*/  UBIFS_DATA_NODE ; 
 int UBIFS_DATA_NODE_SZ ; 
 int WORST_COMPR_FACTOR ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dbg_jnl (char*,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_reservation (struct ubifs_info*) ; 
 int /*<<< orphan*/  key_block (struct ubifs_info*,union ubifs_key const*) ; 
 scalar_t__ key_inum (struct ubifs_info*,union ubifs_key const*) ; 
 int /*<<< orphan*/  key_write (struct ubifs_info*,union ubifs_key const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ubifs_data_node*) ; 
 struct ubifs_data_node* kmalloc (int,int /*<<< orphan*/ ) ; 
 int make_reservation (struct ubifs_info*,size_t,int) ; 
 int /*<<< orphan*/  release_head (struct ubifs_info*,size_t) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_compress (void const*,int,int /*<<< orphan*/ *,int*,int*) ; 
 struct ubifs_inode* ubifs_inode (struct inode const*) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_tnc_add (struct ubifs_info*,union ubifs_key const*,int,int,int) ; 
 int /*<<< orphan*/  ubifs_wbuf_add_ino_nolock (int /*<<< orphan*/ *,scalar_t__) ; 
 int write_node (struct ubifs_info*,size_t,struct ubifs_data_node*,int,int*,int*) ; 
 int /*<<< orphan*/  zero_data_node_unused (struct ubifs_data_node*) ; 

int ubifs_jnl_write_data(struct ubifs_info *c, const struct inode *inode,
			 const union ubifs_key *key, const void *buf, int len)
{
	struct ubifs_data_node *data;
	int err, lnum, offs, compr_type, out_len;
	int dlen = UBIFS_DATA_NODE_SZ + UBIFS_BLOCK_SIZE * WORST_COMPR_FACTOR;
	struct ubifs_inode *ui = ubifs_inode(inode);

	dbg_jnl("ino %lu, blk %u, len %d, key %s",
		(unsigned long)key_inum(c, key), key_block(c, key), len,
		DBGKEY(key));
	ubifs_assert(len <= UBIFS_BLOCK_SIZE);

	data = kmalloc(dlen, GFP_NOFS);
	if (!data)
		return -ENOMEM;

	data->ch.node_type = UBIFS_DATA_NODE;
	key_write(c, key, &data->key);
	data->size = cpu_to_le32(len);
	zero_data_node_unused(data);

	if (!(ui->flags & UBIFS_COMPR_FL))
		/* Compression is disabled for this inode */
		compr_type = UBIFS_COMPR_NONE;
	else
		compr_type = ui->compr_type;

	out_len = dlen - UBIFS_DATA_NODE_SZ;
	ubifs_compress(buf, len, &data->data, &out_len, &compr_type);
	ubifs_assert(out_len <= UBIFS_BLOCK_SIZE);

	dlen = UBIFS_DATA_NODE_SZ + out_len;
	data->compr_type = cpu_to_le16(compr_type);

	/* Make reservation before allocating sequence numbers */
	err = make_reservation(c, DATAHD, dlen);
	if (err)
		goto out_free;

	err = write_node(c, DATAHD, data, dlen, &lnum, &offs);
	if (err)
		goto out_release;
	ubifs_wbuf_add_ino_nolock(&c->jheads[DATAHD].wbuf, key_inum(c, key));
	release_head(c, DATAHD);

	err = ubifs_tnc_add(c, key, lnum, offs, dlen);
	if (err)
		goto out_ro;

	finish_reservation(c);
	kfree(data);
	return 0;

out_release:
	release_head(c, DATAHD);
out_ro:
	ubifs_ro_mode(c, err);
	finish_reservation(c);
out_free:
	kfree(data);
	return err;
}