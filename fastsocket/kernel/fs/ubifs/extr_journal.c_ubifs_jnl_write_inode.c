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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_inode {int /*<<< orphan*/  ui_lock; int /*<<< orphan*/  ui_size; int /*<<< orphan*/  synced_i_size; scalar_t__ data_len; } ;
struct ubifs_ino_node {int dummy; } ;
struct ubifs_info {TYPE_1__* jheads; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_nlink; } ;
struct TYPE_2__ {int /*<<< orphan*/  wbuf; } ;

/* Variables and functions */
 size_t BASEHD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int IS_SYNC (struct inode const*) ; 
 int UBIFS_INO_NODE_SZ ; 
 int /*<<< orphan*/  dbg_jnl (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_reservation (struct ubifs_info*) ; 
 int /*<<< orphan*/  ino_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ubifs_ino_node*) ; 
 struct ubifs_ino_node* kmalloc (int,int /*<<< orphan*/ ) ; 
 int make_reservation (struct ubifs_info*,size_t,int) ; 
 int /*<<< orphan*/  pack_inode (struct ubifs_info*,struct ubifs_ino_node*,struct inode const*,int) ; 
 int /*<<< orphan*/  release_head (struct ubifs_info*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ubifs_add_dirt (struct ubifs_info*,int,int) ; 
 int /*<<< orphan*/  ubifs_delete_orphan (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 struct ubifs_inode* ubifs_inode (struct inode const*) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_tnc_add (struct ubifs_info*,union ubifs_key*,int,int,int) ; 
 int ubifs_tnc_remove_ino (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_wbuf_add_ino_nolock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int write_head (struct ubifs_info*,size_t,struct ubifs_ino_node*,int,int*,int*,int) ; 

int ubifs_jnl_write_inode(struct ubifs_info *c, const struct inode *inode)
{
	int err, lnum, offs;
	struct ubifs_ino_node *ino;
	struct ubifs_inode *ui = ubifs_inode(inode);
	int sync = 0, len = UBIFS_INO_NODE_SZ, last_reference = !inode->i_nlink;

	dbg_jnl("ino %lu, nlink %u", inode->i_ino, inode->i_nlink);

	/*
	 * If the inode is being deleted, do not write the attached data. No
	 * need to synchronize the write-buffer either.
	 */
	if (!last_reference) {
		len += ui->data_len;
		sync = IS_SYNC(inode);
	}
	ino = kmalloc(len, GFP_NOFS);
	if (!ino)
		return -ENOMEM;

	/* Make reservation before allocating sequence numbers */
	err = make_reservation(c, BASEHD, len);
	if (err)
		goto out_free;

	pack_inode(c, ino, inode, 1);
	err = write_head(c, BASEHD, ino, len, &lnum, &offs, sync);
	if (err)
		goto out_release;
	if (!sync)
		ubifs_wbuf_add_ino_nolock(&c->jheads[BASEHD].wbuf,
					  inode->i_ino);
	release_head(c, BASEHD);

	if (last_reference) {
		err = ubifs_tnc_remove_ino(c, inode->i_ino);
		if (err)
			goto out_ro;
		ubifs_delete_orphan(c, inode->i_ino);
		err = ubifs_add_dirt(c, lnum, len);
	} else {
		union ubifs_key key;

		ino_key_init(c, &key, inode->i_ino);
		err = ubifs_tnc_add(c, &key, lnum, offs, len);
	}
	if (err)
		goto out_ro;

	finish_reservation(c);
	spin_lock(&ui->ui_lock);
	ui->synced_i_size = ui->ui_size;
	spin_unlock(&ui->ui_lock);
	kfree(ino);
	return 0;

out_release:
	release_head(c, BASEHD);
out_ro:
	ubifs_ro_mode(c, err);
	finish_reservation(c);
out_free:
	kfree(ino);
	return err;
}