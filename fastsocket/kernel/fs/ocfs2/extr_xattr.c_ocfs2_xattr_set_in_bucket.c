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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  handle; } ;
struct ocfs2_xattr_search {scalar_t__ not_found; struct ocfs2_xattr_entry* here; } ;
struct ocfs2_xattr_info {size_t value_len; int /*<<< orphan*/ * value; int /*<<< orphan*/  name; } ;
struct ocfs2_xattr_entry {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 size_t OCFS2_XATTR_INLINE_SIZE ; 
 size_t OCFS2_XATTR_ROOT_SIZE ; 
 int /*<<< orphan*/  def_xv ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_remove_xs (struct inode*,int /*<<< orphan*/ ,struct ocfs2_xattr_search*) ; 
 int ocfs2_xattr_bucket_set_value_outside (struct inode*,int /*<<< orphan*/ ,struct ocfs2_xattr_search*,char*,size_t) ; 
 int ocfs2_xattr_bucket_value_truncate_xs (struct inode*,struct ocfs2_xattr_search*,size_t,struct ocfs2_xattr_set_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_xattr_is_local (struct ocfs2_xattr_entry*) ; 
 int /*<<< orphan*/  ocfs2_xattr_name_hash (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_set_entry_in_bucket (struct inode*,int /*<<< orphan*/ ,struct ocfs2_xattr_info*,struct ocfs2_xattr_search*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xattr_set_in_bucket(struct inode *inode,
				     struct ocfs2_xattr_info *xi,
				     struct ocfs2_xattr_search *xs,
				     struct ocfs2_xattr_set_ctxt *ctxt)
{
	int ret, local = 1;
	size_t value_len;
	char *val = (char *)xi->value;
	struct ocfs2_xattr_entry *xe = xs->here;
	u32 name_hash = ocfs2_xattr_name_hash(inode, xi->name,
					      strlen(xi->name));

	if (!xs->not_found && !ocfs2_xattr_is_local(xe)) {
		/*
		 * We need to truncate the xattr storage first.
		 *
		 * If both the old and new value are stored to
		 * outside block, we only need to truncate
		 * the storage and then set the value outside.
		 *
		 * If the new value should be stored within block,
		 * we should free all the outside block first and
		 * the modification to the xattr block will be done
		 * by following steps.
		 */
		if (xi->value_len > OCFS2_XATTR_INLINE_SIZE)
			value_len = xi->value_len;
		else
			value_len = 0;

		ret = ocfs2_xattr_bucket_value_truncate_xs(inode, xs,
							   value_len,
							   ctxt);
		if (ret)
			goto out;

		if (value_len)
			goto set_value_outside;
	}

	value_len = xi->value_len;
	/* So we have to handle the inside block change now. */
	if (value_len > OCFS2_XATTR_INLINE_SIZE) {
		/*
		 * If the new value will be stored outside of block,
		 * initalize a new empty value root and insert it first.
		 */
		local = 0;
		xi->value = &def_xv;
		xi->value_len = OCFS2_XATTR_ROOT_SIZE;
	}

	ret = ocfs2_xattr_set_entry_in_bucket(inode, ctxt->handle, xi, xs,
					      name_hash, local);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (value_len <= OCFS2_XATTR_INLINE_SIZE)
		goto out;

	/* allocate the space now for the outside block storage. */
	ret = ocfs2_xattr_bucket_value_truncate_xs(inode, xs,
						   value_len, ctxt);
	if (ret) {
		mlog_errno(ret);

		if (xs->not_found) {
			/*
			 * We can't allocate enough clusters for outside
			 * storage and we have allocated xattr already,
			 * so need to remove it.
			 */
			ocfs2_xattr_bucket_remove_xs(inode, ctxt->handle, xs);
		}
		goto out;
	}

set_value_outside:
	ret = ocfs2_xattr_bucket_set_value_outside(inode, ctxt->handle,
						   xs, val, value_len);
out:
	return ret;
}