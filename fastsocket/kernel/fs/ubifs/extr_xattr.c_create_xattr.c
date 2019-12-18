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
struct ubifs_inode {int data_len; scalar_t__ xattr_cnt; scalar_t__ xattr_names; int xattr; int ui_size; int /*<<< orphan*/  ui_mutex; int /*<<< orphan*/  xattr_size; int /*<<< orphan*/  data; int /*<<< orphan*/  flags; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int new_ino; int new_dent; int dirtied_ino; int /*<<< orphan*/  dirtied_ino_d; int /*<<< orphan*/  new_ino_d; } ;
struct qstr {scalar_t__ len; } ;
struct inode {int i_flags; int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; TYPE_1__* i_mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 scalar_t__ CALC_DENT_SIZE (scalar_t__) ; 
 scalar_t__ CALC_XATTR_BYTES (int) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ MAX_XATTRS_PER_INODE ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFREG ; 
 int S_IRWXUGO ; 
 int S_NOATIME ; 
 int S_NOCMTIME ; 
 int S_NOQUOTA ; 
 int S_SYNC ; 
 int /*<<< orphan*/  UBIFS_XATTR_FL ; 
 scalar_t__ XATTR_LIST_MAX ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  none_address_operations ; 
 int /*<<< orphan*/  none_file_operations ; 
 int /*<<< orphan*/  none_inode_operations ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_current_time (struct inode*) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,struct qstr const*,struct inode*,int /*<<< orphan*/ ,int) ; 
 struct inode* ubifs_new_inode (struct ubifs_info*,struct inode*,int) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 

__attribute__((used)) static int create_xattr(struct ubifs_info *c, struct inode *host,
			const struct qstr *nm, const void *value, int size)
{
	int err;
	struct inode *inode;
	struct ubifs_inode *ui, *host_ui = ubifs_inode(host);
	struct ubifs_budget_req req = { .new_ino = 1, .new_dent = 1,
				.new_ino_d = ALIGN(size, 8), .dirtied_ino = 1,
				.dirtied_ino_d = ALIGN(host_ui->data_len, 8) };

	if (host_ui->xattr_cnt >= MAX_XATTRS_PER_INODE)
		return -ENOSPC;
	/*
	 * Linux limits the maximum size of the extended attribute names list
	 * to %XATTR_LIST_MAX. This means we should not allow creating more
	 * extended attributes if the name list becomes larger. This limitation
	 * is artificial for UBIFS, though.
	 */
	if (host_ui->xattr_names + host_ui->xattr_cnt +
					nm->len + 1 > XATTR_LIST_MAX)
		return -ENOSPC;

	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	inode = ubifs_new_inode(c, host, S_IFREG | S_IRWXUGO);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_budg;
	}

	/* Re-define all operations to be "nothing" */
	inode->i_mapping->a_ops = &none_address_operations;
	inode->i_op = &none_inode_operations;
	inode->i_fop = &none_file_operations;

	inode->i_flags |= S_SYNC | S_NOATIME | S_NOCMTIME | S_NOQUOTA;
	ui = ubifs_inode(inode);
	ui->xattr = 1;
	ui->flags |= UBIFS_XATTR_FL;
	ui->data = kmalloc(size, GFP_NOFS);
	if (!ui->data) {
		err = -ENOMEM;
		goto out_free;
	}
	memcpy(ui->data, value, size);
	inode->i_size = ui->ui_size = size;
	ui->data_len = size;

	mutex_lock(&host_ui->ui_mutex);
	host->i_ctime = ubifs_current_time(host);
	host_ui->xattr_cnt += 1;
	host_ui->xattr_size += CALC_DENT_SIZE(nm->len);
	host_ui->xattr_size += CALC_XATTR_BYTES(size);
	host_ui->xattr_names += nm->len;

	err = ubifs_jnl_update(c, host, nm, inode, 0, 1);
	if (err)
		goto out_cancel;
	mutex_unlock(&host_ui->ui_mutex);

	ubifs_release_budget(c, &req);
	insert_inode_hash(inode);
	iput(inode);
	return 0;

out_cancel:
	host_ui->xattr_cnt -= 1;
	host_ui->xattr_size -= CALC_DENT_SIZE(nm->len);
	host_ui->xattr_size -= CALC_XATTR_BYTES(size);
	mutex_unlock(&host_ui->ui_mutex);
out_free:
	make_bad_inode(inode);
	iput(inode);
out_budg:
	ubifs_release_budget(c, &req);
	return err;
}