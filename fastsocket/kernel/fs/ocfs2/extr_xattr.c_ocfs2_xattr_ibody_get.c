#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_xattr_value_root {int dummy; } ;
struct ocfs2_xattr_search {TYPE_3__* here; void* base; struct ocfs2_xattr_header* header; void* end; TYPE_1__* inode_bh; } ;
struct ocfs2_xattr_header {TYPE_3__* xh_entries; } ;
struct ocfs2_inode_info {int ip_dyn_features; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_xattr_inline_size; } ;
struct inode {TYPE_2__* i_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  xe_name_len; int /*<<< orphan*/  xe_name_offset; int /*<<< orphan*/  xe_value_size; } ;
struct TYPE_5__ {int s_blocksize; } ;
struct TYPE_4__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENODATA ; 
 int ERANGE ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_XATTR_FL ; 
 int OCFS2_XATTR_SIZE (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_xattr_find_entry (int,char const*,struct ocfs2_xattr_search*) ; 
 int ocfs2_xattr_get_value_outside (struct inode*,struct ocfs2_xattr_value_root*,void*,size_t) ; 
 scalar_t__ ocfs2_xattr_is_local (TYPE_3__*) ; 

__attribute__((used)) static int ocfs2_xattr_ibody_get(struct inode *inode,
				 int name_index,
				 const char *name,
				 void *buffer,
				 size_t buffer_size,
				 struct ocfs2_xattr_search *xs)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)xs->inode_bh->b_data;
	struct ocfs2_xattr_value_root *xv;
	size_t size;
	int ret = 0;

	if (!(oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL))
		return -ENODATA;

	xs->end = (void *)di + inode->i_sb->s_blocksize;
	xs->header = (struct ocfs2_xattr_header *)
			(xs->end - le16_to_cpu(di->i_xattr_inline_size));
	xs->base = (void *)xs->header;
	xs->here = xs->header->xh_entries;

	ret = ocfs2_xattr_find_entry(name_index, name, xs);
	if (ret)
		return ret;
	size = le64_to_cpu(xs->here->xe_value_size);
	if (buffer) {
		if (size > buffer_size)
			return -ERANGE;
		if (ocfs2_xattr_is_local(xs->here)) {
			memcpy(buffer, (void *)xs->base +
			       le16_to_cpu(xs->here->xe_name_offset) +
			       OCFS2_XATTR_SIZE(xs->here->xe_name_len), size);
		} else {
			xv = (struct ocfs2_xattr_value_root *)
				(xs->base + le16_to_cpu(
				 xs->here->xe_name_offset) +
				OCFS2_XATTR_SIZE(xs->here->xe_name_len));
			ret = ocfs2_xattr_get_value_outside(inode, xv,
							    buffer, size);
			if (ret < 0) {
				mlog_errno(ret);
				return ret;
			}
		}
	}

	return size;
}