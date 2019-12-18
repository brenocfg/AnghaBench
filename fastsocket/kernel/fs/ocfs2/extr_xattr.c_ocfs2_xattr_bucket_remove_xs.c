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
struct ocfs2_xattr_search {int /*<<< orphan*/  bucket; scalar_t__ here; } ;
struct ocfs2_xattr_header {int /*<<< orphan*/  xh_count; struct ocfs2_xattr_entry* xh_entries; } ;
struct ocfs2_xattr_entry {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_xattr_header* bucket_xh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct ocfs2_xattr_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_xattr_bucket_journal_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_xattr_bucket_remove_xs(struct inode *inode,
					 handle_t *handle,
					 struct ocfs2_xattr_search *xs)
{
	struct ocfs2_xattr_header *xh = bucket_xh(xs->bucket);
	struct ocfs2_xattr_entry *last = &xh->xh_entries[
						le16_to_cpu(xh->xh_count) - 1];
	int ret = 0;

	ret = ocfs2_xattr_bucket_journal_access(handle, xs->bucket,
						OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		return;
	}

	/* Remove the old entry. */
	memmove(xs->here, xs->here + 1,
		(void *)last - (void *)xs->here);
	memset(last, 0, sizeof(struct ocfs2_xattr_entry));
	le16_add_cpu(&xh->xh_count, -1);

	ocfs2_xattr_bucket_journal_dirty(handle, xs->bucket);
}