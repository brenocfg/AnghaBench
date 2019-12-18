#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_sb; TYPE_2__* d_inode; TYPE_1__ d_name; } ;
struct afs_super_info {TYPE_4__* volume; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_3__* cell; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {size_t i_size; int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 scalar_t__ AFSVL_RWVOL ; 
 struct afs_super_info* AFS_FS_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 struct vfsmount* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  _debug (char*,char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  afs_fs_type ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 struct vfsmount* vfs_kern_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static struct vfsmount *afs_mntpt_do_automount(struct dentry *mntpt)
{
	struct afs_super_info *super;
	struct vfsmount *mnt;
	struct page *page = NULL;
	size_t size;
	char *buf, *devname = NULL, *options = NULL;
	int ret;

	_enter("{%s}", mntpt->d_name.name);

	BUG_ON(!mntpt->d_inode);

	ret = -EINVAL;
	size = mntpt->d_inode->i_size;
	if (size > PAGE_SIZE - 1)
		goto error;

	ret = -ENOMEM;
	devname = (char *) get_zeroed_page(GFP_KERNEL);
	if (!devname)
		goto error;

	options = (char *) get_zeroed_page(GFP_KERNEL);
	if (!options)
		goto error;

	/* read the contents of the AFS special symlink */
	page = read_mapping_page(mntpt->d_inode->i_mapping, 0, NULL);
	if (IS_ERR(page)) {
		ret = PTR_ERR(page);
		goto error;
	}

	ret = -EIO;
	if (PageError(page))
		goto error;

	buf = kmap_atomic(page, KM_USER0);
	memcpy(devname, buf, size);
	kunmap_atomic(buf, KM_USER0);
	page_cache_release(page);
	page = NULL;

	/* work out what options we want */
	super = AFS_FS_S(mntpt->d_sb);
	memcpy(options, "cell=", 5);
	strcpy(options + 5, super->volume->cell->name);
	if (super->volume->type == AFSVL_RWVOL)
		strcat(options, ",rwpath");

	/* try and do the mount */
	_debug("--- attempting mount %s -o %s ---", devname, options);
	mnt = vfs_kern_mount(&afs_fs_type, 0, devname, options);
	_debug("--- mount result %p ---", mnt);

	free_page((unsigned long) devname);
	free_page((unsigned long) options);
	_leave(" = %p", mnt);
	return mnt;

error:
	if (page)
		page_cache_release(page);
	if (devname)
		free_page((unsigned long) devname);
	if (options)
		free_page((unsigned long) options);
	_leave(" = %d", ret);
	return ERR_PTR(ret);
}