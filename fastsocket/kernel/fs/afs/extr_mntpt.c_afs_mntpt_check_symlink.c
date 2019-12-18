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
struct page {int dummy; } ;
struct key {int dummy; } ;
struct file {struct key* private_data; } ;
struct TYPE_5__ {size_t size; } ;
struct TYPE_4__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; TYPE_2__ status; TYPE_1__ fid; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_MOUNTPOINT ; 
 TYPE_3__* AFS_VNODE_TO_I (struct afs_vnode*) ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int afs_mntpt_check_symlink(struct afs_vnode *vnode, struct key *key)
{
	struct file file = {
		.private_data = key,
	};
	struct page *page;
	size_t size;
	char *buf;
	int ret;

	_enter("{%x:%u,%u}",
	       vnode->fid.vid, vnode->fid.vnode, vnode->fid.unique);

	/* read the contents of the symlink into the pagecache */
	page = read_mapping_page(AFS_VNODE_TO_I(vnode)->i_mapping, 0, &file);
	if (IS_ERR(page)) {
		ret = PTR_ERR(page);
		goto out;
	}

	ret = -EIO;
	if (PageError(page))
		goto out_free;

	buf = kmap(page);

	/* examine the symlink's contents */
	size = vnode->status.size;
	_debug("symlink to %*.*s", (int) size, (int) size, buf);

	if (size > 2 &&
	    (buf[0] == '%' || buf[0] == '#') &&
	    buf[size - 1] == '.'
	    ) {
		_debug("symlink is a mountpoint");
		spin_lock(&vnode->lock);
		set_bit(AFS_VNODE_MOUNTPOINT, &vnode->flags);
		spin_unlock(&vnode->lock);
	}

	ret = 0;

	kunmap(page);
out_free:
	page_cache_release(page);
out:
	_leave(" = %d", ret);
	return ret;
}