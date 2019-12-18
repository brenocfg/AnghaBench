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
struct ocfs2_xattr_value_buf {int (* vb_access ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  vb_bh; } ;
struct ocfs2_xattr_search {scalar_t__ here; TYPE_1__* header; void* base; } ;
struct ocfs2_xattr_info {int /*<<< orphan*/  name; } ;
struct ocfs2_xattr_entry {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  xh_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 size_t OCFS2_XATTR_ROOT_SIZE ; 
 size_t OCFS2_XATTR_SIZE (size_t) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xattr_cleanup(struct inode *inode,
			       handle_t *handle,
			       struct ocfs2_xattr_info *xi,
			       struct ocfs2_xattr_search *xs,
			       struct ocfs2_xattr_value_buf *vb,
			       size_t offs)
{
	int ret = 0;
	size_t name_len = strlen(xi->name);
	void *val = xs->base + offs;
	size_t size = OCFS2_XATTR_SIZE(name_len) + OCFS2_XATTR_ROOT_SIZE;

	ret = vb->vb_access(handle, INODE_CACHE(inode), vb->vb_bh,
			    OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}
	/* Decrease xattr count */
	le16_add_cpu(&xs->header->xh_count, -1);
	/* Remove the xattr entry and tree root which has already be set*/
	memset((void *)xs->here, 0, sizeof(struct ocfs2_xattr_entry));
	memset(val, 0, size);

	ret = ocfs2_journal_dirty(handle, vb->vb_bh);
	if (ret < 0)
		mlog_errno(ret);
out:
	return ret;
}