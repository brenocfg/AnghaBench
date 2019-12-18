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
typedef  scalar_t__ u64 ;
struct ocfs2_xattr_bucket {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_init_xattr_bucket (struct ocfs2_xattr_bucket*,scalar_t__) ; 
 int ocfs2_read_xattr_bucket (struct ocfs2_xattr_bucket*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_copy_data (struct ocfs2_xattr_bucket*,struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_free (struct ocfs2_xattr_bucket*) ; 
 int ocfs2_xattr_bucket_journal_access (int /*<<< orphan*/ *,struct ocfs2_xattr_bucket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_journal_dirty (int /*<<< orphan*/ *,struct ocfs2_xattr_bucket*) ; 
 struct ocfs2_xattr_bucket* ocfs2_xattr_bucket_new (struct inode*) ; 

__attribute__((used)) static int ocfs2_cp_xattr_bucket(struct inode *inode,
				 handle_t *handle,
				 u64 s_blkno,
				 u64 t_blkno,
				 int t_is_new)
{
	int ret;
	struct ocfs2_xattr_bucket *s_bucket = NULL, *t_bucket = NULL;

	BUG_ON(s_blkno == t_blkno);

	mlog(0, "cp bucket %llu to %llu, target is %d\n",
	     (unsigned long long)s_blkno, (unsigned long long)t_blkno,
	     t_is_new);

	s_bucket = ocfs2_xattr_bucket_new(inode);
	t_bucket = ocfs2_xattr_bucket_new(inode);
	if (!s_bucket || !t_bucket) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_read_xattr_bucket(s_bucket, s_blkno);
	if (ret)
		goto out;

	/*
	 * Even if !t_is_new, we're overwriting t_bucket.  Thus,
	 * there's no need to read it.
	 */
	ret = ocfs2_init_xattr_bucket(t_bucket, t_blkno);
	if (ret)
		goto out;

	/*
	 * Hey, if we're overwriting t_bucket, what difference does
	 * ACCESS_CREATE vs ACCESS_WRITE make?  Well, if we allocated a new
	 * cluster to fill, we came here from
	 * ocfs2_mv_xattr_buckets(), and it is really new -
	 * ACCESS_CREATE is required.  But we also might have moved data
	 * out of t_bucket before extending back into it.
	 * ocfs2_add_new_xattr_bucket() can do this - its call to
	 * ocfs2_add_new_xattr_cluster() may have created a new extent
	 * and copied out the end of the old extent.  Then it re-extends
	 * the old extent back to create space for new xattrs.  That's
	 * how we get here, and the bucket isn't really new.
	 */
	ret = ocfs2_xattr_bucket_journal_access(handle, t_bucket,
						t_is_new ?
						OCFS2_JOURNAL_ACCESS_CREATE :
						OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret)
		goto out;

	ocfs2_xattr_bucket_copy_data(t_bucket, s_bucket);
	ocfs2_xattr_bucket_journal_dirty(handle, t_bucket);

out:
	ocfs2_xattr_bucket_free(t_bucket);
	ocfs2_xattr_bucket_free(s_bucket);

	return ret;
}