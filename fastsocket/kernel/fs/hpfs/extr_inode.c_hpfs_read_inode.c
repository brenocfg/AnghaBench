#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct super_block {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * a_ops; } ;
struct inode {int i_mode; int i_nlink; int i_size; int i_blocks; TYPE_3__ i_data; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; struct super_block* i_sb; void* i_gid; void* i_uid; int /*<<< orphan*/  i_ino; } ;
struct hpfs_inode_info {int i_ea_uid; int i_ea_gid; int i_ea_mode; int mmu_private; int /*<<< orphan*/  i_dno; int /*<<< orphan*/  i_parent_dir; } ;
struct TYPE_6__ {TYPE_1__* external; } ;
struct fnode {int file_size; TYPE_2__ u; int /*<<< orphan*/  up; scalar_t__ dirflag; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_8__ {int sb_mode; int sb_chk; scalar_t__ sb_eas; } ;
struct TYPE_5__ {int /*<<< orphan*/  disk_secno; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IFLNK ; 
 int S_IFREG ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  hpfs_aops ; 
 int /*<<< orphan*/  hpfs_count_dnodes (struct super_block*,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpfs_dir_iops ; 
 int /*<<< orphan*/  hpfs_dir_ops ; 
 int /*<<< orphan*/  hpfs_file_iops ; 
 int /*<<< orphan*/  hpfs_file_ops ; 
 unsigned char* hpfs_get_ea (struct super_block*,struct fnode*,char*,int*) ; 
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 struct fnode* hpfs_map_fnode (struct super_block*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 TYPE_4__* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  hpfs_symlink_aops ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  new_decode_dev (int) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 

void hpfs_read_inode(struct inode *i)
{
	struct buffer_head *bh;
	struct fnode *fnode;
	struct super_block *sb = i->i_sb;
	struct hpfs_inode_info *hpfs_inode = hpfs_i(i);
	unsigned char *ea;
	int ea_size;

	if (!(fnode = hpfs_map_fnode(sb, i->i_ino, &bh))) {
		/*i->i_mode |= S_IFREG;
		i->i_mode &= ~0111;
		i->i_op = &hpfs_file_iops;
		i->i_fop = &hpfs_file_ops;
		i->i_nlink = 0;*/
		make_bad_inode(i);
		return;
	}
	if (hpfs_sb(i->i_sb)->sb_eas) {
		if ((ea = hpfs_get_ea(i->i_sb, fnode, "UID", &ea_size))) {
			if (ea_size == 2) {
				i->i_uid = le16_to_cpu(*(__le16*)ea);
				hpfs_inode->i_ea_uid = 1;
			}
			kfree(ea);
		}
		if ((ea = hpfs_get_ea(i->i_sb, fnode, "GID", &ea_size))) {
			if (ea_size == 2) {
				i->i_gid = le16_to_cpu(*(__le16*)ea);
				hpfs_inode->i_ea_gid = 1;
			}
			kfree(ea);
		}
		if ((ea = hpfs_get_ea(i->i_sb, fnode, "SYMLINK", &ea_size))) {
			kfree(ea);
			i->i_mode = S_IFLNK | 0777;
			i->i_op = &page_symlink_inode_operations;
			i->i_data.a_ops = &hpfs_symlink_aops;
			i->i_nlink = 1;
			i->i_size = ea_size;
			i->i_blocks = 1;
			brelse(bh);
			return;
		}
		if ((ea = hpfs_get_ea(i->i_sb, fnode, "MODE", &ea_size))) {
			int rdev = 0;
			umode_t mode = hpfs_sb(sb)->sb_mode;
			if (ea_size == 2) {
				mode = le16_to_cpu(*(__le16*)ea);
				hpfs_inode->i_ea_mode = 1;
			}
			kfree(ea);
			i->i_mode = mode;
			if (S_ISBLK(mode) || S_ISCHR(mode)) {
				if ((ea = hpfs_get_ea(i->i_sb, fnode, "DEV", &ea_size))) {
					if (ea_size == 4)
						rdev = le32_to_cpu(*(__le32*)ea);
					kfree(ea);
				}
			}
			if (S_ISBLK(mode) || S_ISCHR(mode) || S_ISFIFO(mode) || S_ISSOCK(mode)) {
				brelse(bh);
				i->i_nlink = 1;
				i->i_size = 0;
				i->i_blocks = 1;
				init_special_inode(i, mode,
					new_decode_dev(rdev));
				return;
			}
		}
	}
	if (fnode->dirflag) {
		unsigned n_dnodes, n_subdirs;
		i->i_mode |= S_IFDIR;
		i->i_op = &hpfs_dir_iops;
		i->i_fop = &hpfs_dir_ops;
		hpfs_inode->i_parent_dir = fnode->up;
		hpfs_inode->i_dno = fnode->u.external[0].disk_secno;
		if (hpfs_sb(sb)->sb_chk >= 2) {
			struct buffer_head *bh0;
			if (hpfs_map_fnode(sb, hpfs_inode->i_parent_dir, &bh0)) brelse(bh0);
		}
		n_dnodes = 0; n_subdirs = 0;
		hpfs_count_dnodes(i->i_sb, hpfs_inode->i_dno, &n_dnodes, &n_subdirs, NULL);
		i->i_blocks = 4 * n_dnodes;
		i->i_size = 2048 * n_dnodes;
		i->i_nlink = 2 + n_subdirs;
	} else {
		i->i_mode |= S_IFREG;
		if (!hpfs_inode->i_ea_mode) i->i_mode &= ~0111;
		i->i_op = &hpfs_file_iops;
		i->i_fop = &hpfs_file_ops;
		i->i_nlink = 1;
		i->i_size = fnode->file_size;
		i->i_blocks = ((i->i_size + 511) >> 9) + 1;
		i->i_data.a_ops = &hpfs_aops;
		hpfs_i(i)->mmu_private = i->i_size;
	}
	brelse(bh);
}