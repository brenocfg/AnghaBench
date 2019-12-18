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
struct ubifs_inode {long long compr_type; scalar_t__ xattr_names; scalar_t__ xattr_cnt; scalar_t__ data_len; scalar_t__ xattr; } ;
struct ubifs_info {scalar_t__ max_inode_sz; } ;
struct inode {scalar_t__ i_size; int i_mode; int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int S_IFMT ; 
 int S_IFREG ; 
 long long UBIFS_COMPR_TYPES_CNT ; 
 scalar_t__ UBIFS_MAX_INO_DATA ; 
 scalar_t__ XATTR_LIST_MAX ; 
 int dbg_check_dir_size (struct ubifs_info*,struct inode const*) ; 
 int /*<<< orphan*/  ubifs_compr_name (long long) ; 
 int /*<<< orphan*/  ubifs_compr_present (long long) ; 
 int /*<<< orphan*/  ubifs_err (char*,long long) ; 
 struct ubifs_inode* ubifs_inode (struct inode const*) ; 
 int /*<<< orphan*/  ubifs_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_inode(struct ubifs_info *c, const struct inode *inode)
{
	int err;
	const struct ubifs_inode *ui = ubifs_inode(inode);

	if (inode->i_size > c->max_inode_sz) {
		ubifs_err("inode is too large (%lld)",
			  (long long)inode->i_size);
		return 1;
	}

	if (ui->compr_type < 0 || ui->compr_type >= UBIFS_COMPR_TYPES_CNT) {
		ubifs_err("unknown compression type %d", ui->compr_type);
		return 2;
	}

	if (ui->xattr_names + ui->xattr_cnt > XATTR_LIST_MAX)
		return 3;

	if (ui->data_len < 0 || ui->data_len > UBIFS_MAX_INO_DATA)
		return 4;

	if (ui->xattr && (inode->i_mode & S_IFMT) != S_IFREG)
		return 5;

	if (!ubifs_compr_present(ui->compr_type)) {
		ubifs_warn("inode %lu uses '%s' compression, but it was not "
			   "compiled in", inode->i_ino,
			   ubifs_compr_name(ui->compr_type));
	}

	err = dbg_check_dir_size(c, inode);
	return err;
}