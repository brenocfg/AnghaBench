#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_7__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct ext3_dir_entry_2 {int dummy; } ;
struct dx_hash_info {scalar_t__ hash_version; int hash; scalar_t__ minor_hash; int /*<<< orphan*/  seed; } ;
struct dx_frame {int /*<<< orphan*/  at; TYPE_3__* bh; } ;
typedef  int __u32 ;
struct TYPE_10__ {int i_flags; } ;
struct TYPE_9__ {scalar_t__ s_def_hash_version; scalar_t__ s_hash_unsigned; int /*<<< orphan*/  s_hash_seed; } ;
struct TYPE_8__ {scalar_t__ b_data; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ DX_HASH_TEA ; 
 TYPE_5__* EXT3_I (struct inode*) ; 
 int EXT3_INDEX_FL ; 
 TYPE_4__* EXT3_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_NB_ALWAYS ; 
 int dx_get_block (int /*<<< orphan*/ ) ; 
 struct dx_frame* dx_probe (int /*<<< orphan*/ *,struct inode*,struct dx_hash_info*,struct dx_frame*,int*) ; 
 int /*<<< orphan*/  dx_release (struct dx_frame*) ; 
 int /*<<< orphan*/  dxtrace (int /*<<< orphan*/ ) ; 
 int ext3_htree_next_block (struct inode*,int /*<<< orphan*/ ,struct dx_frame*,struct dx_frame*,int*) ; 
 int ext3_htree_store_dirent (struct file*,int,int /*<<< orphan*/ ,struct ext3_dir_entry_2*) ; 
 struct ext3_dir_entry_2* ext3_next_entry (struct ext3_dir_entry_2*) ; 
 int htree_dirblock_to_tree (struct file*,struct inode*,int,struct dx_hash_info*,int,int) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 

int ext3_htree_fill_tree(struct file *dir_file, __u32 start_hash,
			 __u32 start_minor_hash, __u32 *next_hash)
{
	struct dx_hash_info hinfo;
	struct ext3_dir_entry_2 *de;
	struct dx_frame frames[2], *frame;
	struct inode *dir;
	int block, err;
	int count = 0;
	int ret;
	__u32 hashval;

	dxtrace(printk("In htree_fill_tree, start hash: %x:%x\n", start_hash,
		       start_minor_hash));
	dir = dir_file->f_path.dentry->d_inode;
	if (!(EXT3_I(dir)->i_flags & EXT3_INDEX_FL)) {
		hinfo.hash_version = EXT3_SB(dir->i_sb)->s_def_hash_version;
		if (hinfo.hash_version <= DX_HASH_TEA)
			hinfo.hash_version +=
				EXT3_SB(dir->i_sb)->s_hash_unsigned;
		hinfo.seed = EXT3_SB(dir->i_sb)->s_hash_seed;
		count = htree_dirblock_to_tree(dir_file, dir, 0, &hinfo,
					       start_hash, start_minor_hash);
		*next_hash = ~0;
		return count;
	}
	hinfo.hash = start_hash;
	hinfo.minor_hash = 0;
	frame = dx_probe(NULL, dir_file->f_path.dentry->d_inode, &hinfo, frames, &err);
	if (!frame)
		return err;

	/* Add '.' and '..' from the htree header */
	if (!start_hash && !start_minor_hash) {
		de = (struct ext3_dir_entry_2 *) frames[0].bh->b_data;
		if ((err = ext3_htree_store_dirent(dir_file, 0, 0, de)) != 0)
			goto errout;
		count++;
	}
	if (start_hash < 2 || (start_hash ==2 && start_minor_hash==0)) {
		de = (struct ext3_dir_entry_2 *) frames[0].bh->b_data;
		de = ext3_next_entry(de);
		if ((err = ext3_htree_store_dirent(dir_file, 2, 0, de)) != 0)
			goto errout;
		count++;
	}

	while (1) {
		block = dx_get_block(frame->at);
		ret = htree_dirblock_to_tree(dir_file, dir, block, &hinfo,
					     start_hash, start_minor_hash);
		if (ret < 0) {
			err = ret;
			goto errout;
		}
		count += ret;
		hashval = ~0;
		ret = ext3_htree_next_block(dir, HASH_NB_ALWAYS,
					    frame, frames, &hashval);
		*next_hash = hashval;
		if (ret < 0) {
			err = ret;
			goto errout;
		}
		/*
		 * Stop if:  (a) there are no more entries, or
		 * (b) we have inserted at least one entry and the
		 * next hash value is not a continuation
		 */
		if ((ret == 0) ||
		    (count && ((hashval & 1) == 0)))
			break;
	}
	dx_release(frames);
	dxtrace(printk("Fill tree: returned %d entries, next hash: %x\n",
		       count, *next_hash));
	return count;
errout:
	dx_release(frames);
	return (err);
}