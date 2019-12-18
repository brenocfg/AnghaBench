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
struct ocfs2_super {int dummy; } ;
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * member_0; } ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mode; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_ORPHAN_NAMELEN ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_add_links_count (struct ocfs2_dinode*,int) ; 
 int ocfs2_blkno_stringify (scalar_t__,char*) ; 
 int ocfs2_delete_entry (int /*<<< orphan*/ *,struct inode*,struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_find_entry (char*,int /*<<< orphan*/ ,struct inode*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_free_dir_lookup_result (struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_read_links_count (struct ocfs2_dinode*) ; 

int ocfs2_orphan_del(struct ocfs2_super *osb,
		     handle_t *handle,
		     struct inode *orphan_dir_inode,
		     struct inode *inode,
		     struct buffer_head *orphan_dir_bh)
{
	char name[OCFS2_ORPHAN_NAMELEN + 1];
	struct ocfs2_dinode *orphan_fe;
	int status = 0;
	struct ocfs2_dir_lookup_result lookup = { NULL, };

	mlog_entry_void();

	status = ocfs2_blkno_stringify(OCFS2_I(inode)->ip_blkno, name);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	mlog(0, "removing '%s' from orphan dir %llu (namelen=%d)\n",
	     name, (unsigned long long)OCFS2_I(orphan_dir_inode)->ip_blkno,
	     OCFS2_ORPHAN_NAMELEN);

	/* find it's spot in the orphan directory */
	status = ocfs2_find_entry(name, OCFS2_ORPHAN_NAMELEN, orphan_dir_inode,
				  &lookup);
	if (status) {
		mlog_errno(status);
		goto leave;
	}

	/* remove it from the orphan directory */
	status = ocfs2_delete_entry(handle, orphan_dir_inode, &lookup);
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

	/* do the i_nlink dance! :) */
	orphan_fe = (struct ocfs2_dinode *) orphan_dir_bh->b_data;
	if (S_ISDIR(inode->i_mode))
		ocfs2_add_links_count(orphan_fe, -1);
	orphan_dir_inode->i_nlink = ocfs2_read_links_count(orphan_fe);

	status = ocfs2_journal_dirty(handle, orphan_dir_bh);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

leave:
	ocfs2_free_dir_lookup_result(&lookup);

	mlog_exit(status);
	return status;
}