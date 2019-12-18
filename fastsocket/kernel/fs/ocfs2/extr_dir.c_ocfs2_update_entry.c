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
struct ocfs2_dir_lookup_result {struct buffer_head* dl_leaf_bh; struct ocfs2_dir_entry* dl_entry; } ;
struct ocfs2_dir_entry {int /*<<< orphan*/  inode; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct buffer_head {int dummy; } ;
typedef  int (* ocfs2_journal_access_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int ip_dyn_features; int /*<<< orphan*/  ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_journal_access_db (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_set_de_type (struct ocfs2_dir_entry*,int /*<<< orphan*/ ) ; 

int ocfs2_update_entry(struct inode *dir, handle_t *handle,
		       struct ocfs2_dir_lookup_result *res,
		       struct inode *new_entry_inode)
{
	int ret;
	ocfs2_journal_access_func access = ocfs2_journal_access_db;
	struct ocfs2_dir_entry *de = res->dl_entry;
	struct buffer_head *de_bh = res->dl_leaf_bh;

	/*
	 * The same code works fine for both inline-data and extent
	 * based directories, so no need to split this up.  The only
	 * difference is the journal_access function.
	 */

	if (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		access = ocfs2_journal_access_di;

	ret = access(handle, INODE_CACHE(dir), de_bh,
		     OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	de->inode = cpu_to_le64(OCFS2_I(new_entry_inode)->ip_blkno);
	ocfs2_set_de_type(de, new_entry_inode->i_mode);

	ocfs2_journal_dirty(handle, de_bh);

out:
	return ret;
}