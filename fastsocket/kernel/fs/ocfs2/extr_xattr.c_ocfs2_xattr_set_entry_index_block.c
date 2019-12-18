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
typedef  int u16 ;
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  handle; } ;
struct ocfs2_xattr_search {int not_found; int /*<<< orphan*/  xattr_bh; int /*<<< orphan*/  bucket; struct ocfs2_xattr_entry* here; struct ocfs2_xattr_header* header; } ;
struct ocfs2_xattr_info {scalar_t__ value_len; int /*<<< orphan*/  name; int /*<<< orphan*/  name_index; scalar_t__ value; } ;
struct ocfs2_xattr_header {int /*<<< orphan*/  xh_free_start; int /*<<< orphan*/  xh_name_value_len; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_value_size; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {size_t s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODATA ; 
 int OCFS2_XATTR_BUCKET_SIZE ; 
 int OCFS2_XATTR_HEADER_GAP ; 
 scalar_t__ OCFS2_XATTR_INLINE_SIZE ; 
 size_t OCFS2_XATTR_ROOT_SIZE ; 
 size_t OCFS2_XATTR_SIZE (size_t) ; 
 scalar_t__ bucket_blkno (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,unsigned long long,int) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_add_new_xattr_bucket (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_xattr_set_ctxt*) ; 
 int ocfs2_check_xattr_bucket_collision (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_defrag_xattr_bucket (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_relse (int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_index_block_find (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_xattr_search*) ; 
 scalar_t__ ocfs2_xattr_is_local (struct ocfs2_xattr_entry*) ; 
 int ocfs2_xattr_max_xe_in_bucket (TYPE_1__*) ; 
 int ocfs2_xattr_set_in_bucket (struct inode*,struct ocfs2_xattr_info*,struct ocfs2_xattr_search*,struct ocfs2_xattr_set_ctxt*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xattr_set_entry_index_block(struct inode *inode,
					     struct ocfs2_xattr_info *xi,
					     struct ocfs2_xattr_search *xs,
					     struct ocfs2_xattr_set_ctxt *ctxt)
{
	struct ocfs2_xattr_header *xh;
	struct ocfs2_xattr_entry *xe;
	u16 count, header_size, xh_free_start;
	int free, max_free, need, old;
	size_t value_size = 0, name_len = strlen(xi->name);
	size_t blocksize = inode->i_sb->s_blocksize;
	int ret, allocation = 0;

	mlog_entry("Set xattr %s in xattr index block\n", xi->name);

try_again:
	xh = xs->header;
	count = le16_to_cpu(xh->xh_count);
	xh_free_start = le16_to_cpu(xh->xh_free_start);
	header_size = sizeof(struct ocfs2_xattr_header) +
			count * sizeof(struct ocfs2_xattr_entry);
	max_free = OCFS2_XATTR_BUCKET_SIZE - header_size -
		le16_to_cpu(xh->xh_name_value_len) - OCFS2_XATTR_HEADER_GAP;

	mlog_bug_on_msg(header_size > blocksize, "bucket %llu has header size "
			"of %u which exceed block size\n",
			(unsigned long long)bucket_blkno(xs->bucket),
			header_size);

	if (xi->value && xi->value_len > OCFS2_XATTR_INLINE_SIZE)
		value_size = OCFS2_XATTR_ROOT_SIZE;
	else if (xi->value)
		value_size = OCFS2_XATTR_SIZE(xi->value_len);

	if (xs->not_found)
		need = sizeof(struct ocfs2_xattr_entry) +
			OCFS2_XATTR_SIZE(name_len) + value_size;
	else {
		need = value_size + OCFS2_XATTR_SIZE(name_len);

		/*
		 * We only replace the old value if the new length is smaller
		 * than the old one. Otherwise we will allocate new space in the
		 * bucket to store it.
		 */
		xe = xs->here;
		if (ocfs2_xattr_is_local(xe))
			old = OCFS2_XATTR_SIZE(le64_to_cpu(xe->xe_value_size));
		else
			old = OCFS2_XATTR_SIZE(OCFS2_XATTR_ROOT_SIZE);

		if (old >= value_size)
			need = 0;
	}

	free = xh_free_start - header_size - OCFS2_XATTR_HEADER_GAP;
	/*
	 * We need to make sure the new name/value pair
	 * can exist in the same block.
	 */
	if (xh_free_start % blocksize < need)
		free -= xh_free_start % blocksize;

	mlog(0, "xs->not_found = %d, in xattr bucket %llu: free = %d, "
	     "need = %d, max_free = %d, xh_free_start = %u, xh_name_value_len ="
	     " %u\n", xs->not_found,
	     (unsigned long long)bucket_blkno(xs->bucket),
	     free, need, max_free, le16_to_cpu(xh->xh_free_start),
	     le16_to_cpu(xh->xh_name_value_len));

	if (free < need ||
	    (xs->not_found &&
	     count == ocfs2_xattr_max_xe_in_bucket(inode->i_sb))) {
		if (need <= max_free &&
		    count < ocfs2_xattr_max_xe_in_bucket(inode->i_sb)) {
			/*
			 * We can create the space by defragment. Since only the
			 * name/value will be moved, the xe shouldn't be changed
			 * in xs.
			 */
			ret = ocfs2_defrag_xattr_bucket(inode, ctxt->handle,
							xs->bucket);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}

			xh_free_start = le16_to_cpu(xh->xh_free_start);
			free = xh_free_start - header_size
				- OCFS2_XATTR_HEADER_GAP;
			if (xh_free_start % blocksize < need)
				free -= xh_free_start % blocksize;

			if (free >= need)
				goto xattr_set;

			mlog(0, "Can't get enough space for xattr insert by "
			     "defragment. Need %u bytes, but we have %d, so "
			     "allocate new bucket for it.\n", need, free);
		}

		/*
		 * We have to add new buckets or clusters and one
		 * allocation should leave us enough space for insert.
		 */
		BUG_ON(allocation);

		/*
		 * We do not allow for overlapping ranges between buckets. And
		 * the maximum number of collisions we will allow for then is
		 * one bucket's worth, so check it here whether we need to
		 * add a new bucket for the insert.
		 */
		ret = ocfs2_check_xattr_bucket_collision(inode,
							 xs->bucket,
							 xi->name);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		ret = ocfs2_add_new_xattr_bucket(inode,
						 xs->xattr_bh,
						 xs->bucket,
						 ctxt);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		/*
		 * ocfs2_add_new_xattr_bucket() will have updated
		 * xs->bucket if it moved, but it will not have updated
		 * any of the other search fields.  Thus, we drop it and
		 * re-search.  Everything should be cached, so it'll be
		 * quick.
		 */
		ocfs2_xattr_bucket_relse(xs->bucket);
		ret = ocfs2_xattr_index_block_find(inode, xs->xattr_bh,
						   xi->name_index,
						   xi->name, xs);
		if (ret && ret != -ENODATA)
			goto out;
		xs->not_found = ret;
		allocation = 1;
		goto try_again;
	}

xattr_set:
	ret = ocfs2_xattr_set_in_bucket(inode, xi, xs, ctxt);
out:
	mlog_exit(ret);
	return ret;
}