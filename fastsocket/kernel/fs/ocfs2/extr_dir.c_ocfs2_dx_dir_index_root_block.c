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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  de_num_used; } ;
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_num_entries; TYPE_2__ dr_entries; } ;
struct ocfs2_dx_hinfo {int /*<<< orphan*/  minor_hash; int /*<<< orphan*/  major_hash; } ;
struct ocfs2_dir_entry {int /*<<< orphan*/  rec_len; int /*<<< orphan*/  name; int /*<<< orphan*/  name_len; int /*<<< orphan*/  inode; } ;
struct inode {scalar_t__ i_ino; TYPE_1__* i_sb; } ;
struct buffer_head {char* b_data; int /*<<< orphan*/  b_blocknr; } ;
struct TYPE_3__ {int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_dx_dir_name_hash (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_dx_hinfo*) ; 
 int /*<<< orphan*/  ocfs2_dx_entry_list_insert (TYPE_2__*,struct ocfs2_dx_hinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_dx_dir_index_root_block(struct inode *dir,
					 struct buffer_head *dx_root_bh,
					 struct buffer_head *dirent_bh)
{
	char *de_buf, *limit;
	struct ocfs2_dx_root_block *dx_root;
	struct ocfs2_dir_entry *de;
	struct ocfs2_dx_hinfo hinfo;
	u64 dirent_blk = dirent_bh->b_blocknr;

	dx_root = (struct ocfs2_dx_root_block *)dx_root_bh->b_data;

	de_buf = dirent_bh->b_data;
	limit = de_buf + dir->i_sb->s_blocksize;

	while (de_buf < limit) {
		de = (struct ocfs2_dir_entry *)de_buf;

		if (!de->name_len || !de->inode)
			goto inc;

		ocfs2_dx_dir_name_hash(dir, de->name, de->name_len, &hinfo);

		mlog(0,
		     "dir: %llu, major: 0x%x minor: 0x%x, index: %u, name: %.*s\n",
		     (unsigned long long)dir->i_ino, hinfo.major_hash,
		     hinfo.minor_hash,
		     le16_to_cpu(dx_root->dr_entries.de_num_used),
		     de->name_len, de->name);

		ocfs2_dx_entry_list_insert(&dx_root->dr_entries, &hinfo,
					   dirent_blk);

		le32_add_cpu(&dx_root->dr_num_entries, 1);
inc:
		de_buf += le16_to_cpu(de->rec_len);
	}
}