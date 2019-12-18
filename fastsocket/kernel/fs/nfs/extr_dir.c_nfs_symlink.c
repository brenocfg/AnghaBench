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
struct pagevec {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct iattr {int ia_mode; int /*<<< orphan*/  ia_valid; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_3__* d_inode; TYPE_2__ d_name; } ;
struct TYPE_8__ {int (* symlink ) (struct inode*,struct dentry*,struct page*,unsigned int,struct iattr*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_HIGHUSER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KM_USER0 ; 
 TYPE_4__* NFS_PROTO (struct inode*) ; 
 unsigned int PAGE_SIZE ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  add_to_page_cache (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,...) ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_lru_add_file (struct pagevec*) ; 
 unsigned int strlen (char const*) ; 
 int stub1 (struct inode*,struct dentry*,struct page*,unsigned int,struct iattr*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int nfs_symlink(struct inode *dir, struct dentry *dentry, const char *symname)
{
	struct pagevec lru_pvec;
	struct page *page;
	char *kaddr;
	struct iattr attr;
	unsigned int pathlen = strlen(symname);
	int error;

	dfprintk(VFS, "NFS: symlink(%s/%ld, %s, %s)\n", dir->i_sb->s_id,
		dir->i_ino, dentry->d_name.name, symname);

	if (pathlen > PAGE_SIZE)
		return -ENAMETOOLONG;

	attr.ia_mode = S_IFLNK | S_IRWXUGO;
	attr.ia_valid = ATTR_MODE;

	page = alloc_page(GFP_HIGHUSER);
	if (!page)
		return -ENOMEM;

	kaddr = kmap_atomic(page, KM_USER0);
	memcpy(kaddr, symname, pathlen);
	if (pathlen < PAGE_SIZE)
		memset(kaddr + pathlen, 0, PAGE_SIZE - pathlen);
	kunmap_atomic(kaddr, KM_USER0);

	error = NFS_PROTO(dir)->symlink(dir, dentry, page, pathlen, &attr);
	if (error != 0) {
		dfprintk(VFS, "NFS: symlink(%s/%ld, %s, %s) error %d\n",
			dir->i_sb->s_id, dir->i_ino,
			dentry->d_name.name, symname, error);
		d_drop(dentry);
		__free_page(page);
		return error;
	}

	/*
	 * No big deal if we can't add this page to the page cache here.
	 * READLINK will get the missing page from the server if needed.
	 */
	pagevec_init(&lru_pvec, 0);
	if (!add_to_page_cache(page, dentry->d_inode->i_mapping, 0,
							GFP_KERNEL)) {
		pagevec_add(&lru_pvec, page);
		pagevec_lru_add_file(&lru_pvec);
		SetPageUptodate(page);
		unlock_page(page);
	} else
		__free_page(page);

	return 0;
}