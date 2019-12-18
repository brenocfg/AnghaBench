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
struct ocfs2_super {int /*<<< orphan*/  slot_num; } ;
struct ocfs2_dir_lookup_result {int dummy; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_orphaned_slot; int /*<<< orphan*/  i_flags; } ;
struct inode {int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_ORPHANED_FL ; 
 int /*<<< orphan*/  OCFS2_ORPHAN_NAMELEN ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int __ocfs2_add_entry (int /*<<< orphan*/ *,struct inode*,char*,int /*<<< orphan*/ ,struct inode*,scalar_t__,struct buffer_head*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_add_links_count (struct ocfs2_dinode*,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_read_links_count (struct ocfs2_dinode*) ; 

__attribute__((used)) static int ocfs2_orphan_add(struct ocfs2_super *osb,
			    handle_t *handle,
			    struct inode *inode,
			    struct ocfs2_dinode *fe,
			    char *name,
			    struct ocfs2_dir_lookup_result *lookup,
			    struct inode *orphan_dir_inode)
{
	struct buffer_head *orphan_dir_bh = NULL;
	int status = 0;
	struct ocfs2_dinode *orphan_fe;

	mlog_entry("(inode->i_ino = %lu)\n", inode->i_ino);

	status = ocfs2_read_inode_block(orphan_dir_inode, &orphan_dir_bh);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(orphan_dir_inode),
					 orphan_dir_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	/* we're a cluster, and nlink can change on disk from
	 * underneath us... */
	orphan_fe = (struct ocfs2_dinode *) orphan_dir_bh->b_data;
	if (S_ISDIR(inode->i_mode))
		ocfs2_add_links_count(orphan_fe, 1);
	orphan_dir_inode->i_nlink = ocfs2_read_links_count(orphan_fe);

	status = ocfs2_journal_dirty(handle, orphan_dir_bh);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	status = __ocfs2_add_entry(handle, orphan_dir_inode, name,
				   OCFS2_ORPHAN_NAMELEN, inode,
				   OCFS2_I(inode)->ip_blkno,
				   orphan_dir_bh, lookup);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	le32_add_cpu(&fe->i_flags, OCFS2_ORPHANED_FL);

	/* Record which orphan dir our inode now resides
	 * in. delete_inode will use this to determine which orphan
	 * dir to lock. */
	fe->i_orphaned_slot = cpu_to_le16(osb->slot_num);

	mlog(0, "Inode %llu orphaned in slot %d\n",
	     (unsigned long long)OCFS2_I(inode)->ip_blkno, osb->slot_num);

leave:
	brelse(orphan_dir_bh);

	mlog_exit(status);
	return status;
}