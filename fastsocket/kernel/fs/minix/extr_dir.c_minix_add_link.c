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
struct super_block {int dummy; } ;
struct page {int /*<<< orphan*/  mapping; } ;
struct minix_sb_info {char* s_dirsize; scalar_t__ s_version; int /*<<< orphan*/  s_namelen; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; scalar_t__ i_ino; struct super_block* i_sb; } ;
struct TYPE_6__ {char* name; int len; } ;
struct dentry {TYPE_2__ d_name; TYPE_1__* d_parent; } ;
struct TYPE_7__ {char* name; scalar_t__ inode; } ;
typedef  TYPE_3__ minix_dirent ;
struct TYPE_8__ {char* name; scalar_t__ inode; } ;
typedef  TYPE_4__ minix3_dirent ;
typedef  int loff_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOP_FLAG_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ MINIX_V3 ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int __minix_write_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 int dir_commit_chunk (struct page*,int,char*) ; 
 struct page* dir_get_page (struct inode*,unsigned long) ; 
 unsigned long dir_pages (struct inode*) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,char*) ; 
 int minix_last_byte (struct inode*,unsigned long) ; 
 char* minix_next_entry (char*,struct minix_sb_info*) ; 
 struct minix_sb_info* minix_sb (struct super_block*) ; 
 scalar_t__ namecompare (int,int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ page_address (struct page*) ; 
 int page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int minix_add_link(struct dentry *dentry, struct inode *inode)
{
	struct inode *dir = dentry->d_parent->d_inode;
	const char * name = dentry->d_name.name;
	int namelen = dentry->d_name.len;
	struct super_block * sb = dir->i_sb;
	struct minix_sb_info * sbi = minix_sb(sb);
	struct page *page = NULL;
	unsigned long npages = dir_pages(dir);
	unsigned long n;
	char *kaddr, *p;
	minix_dirent *de;
	minix3_dirent *de3;
	loff_t pos;
	int err;
	char *namx = NULL;
	__u32 inumber;

	/*
	 * We take care of directory expansion in the same loop
	 * This code plays outside i_size, so it locks the page
	 * to protect that region.
	 */
	for (n = 0; n <= npages; n++) {
		char *limit, *dir_end;

		page = dir_get_page(dir, n);
		err = PTR_ERR(page);
		if (IS_ERR(page))
			goto out;
		lock_page(page);
		kaddr = (char*)page_address(page);
		dir_end = kaddr + minix_last_byte(dir, n);
		limit = kaddr + PAGE_CACHE_SIZE - sbi->s_dirsize;
		for (p = kaddr; p <= limit; p = minix_next_entry(p, sbi)) {
			de = (minix_dirent *)p;
			de3 = (minix3_dirent *)p;
			if (sbi->s_version == MINIX_V3) {
				namx = de3->name;
				inumber = de3->inode;
		 	} else {
  				namx = de->name;
				inumber = de->inode;
			}
			if (p == dir_end) {
				/* We hit i_size */
				if (sbi->s_version == MINIX_V3)
					de3->inode = 0;
		 		else
					de->inode = 0;
				goto got_it;
			}
			if (!inumber)
				goto got_it;
			err = -EEXIST;
			if (namecompare(namelen, sbi->s_namelen, name, namx))
				goto out_unlock;
		}
		unlock_page(page);
		dir_put_page(page);
	}
	BUG();
	return -EINVAL;

got_it:
	pos = page_offset(page) + p - (char *)page_address(page);
	err = __minix_write_begin(NULL, page->mapping, pos, sbi->s_dirsize,
					AOP_FLAG_UNINTERRUPTIBLE, &page, NULL);
	if (err)
		goto out_unlock;
	memcpy (namx, name, namelen);
	if (sbi->s_version == MINIX_V3) {
		memset (namx + namelen, 0, sbi->s_dirsize - namelen - 4);
		de3->inode = inode->i_ino;
	} else {
		memset (namx + namelen, 0, sbi->s_dirsize - namelen - 2);
		de->inode = inode->i_ino;
	}
	err = dir_commit_chunk(page, pos, sbi->s_dirsize);
	dir->i_mtime = dir->i_ctime = CURRENT_TIME_SEC;
	mark_inode_dirty(dir);
out_put:
	dir_put_page(page);
out:
	return err;
out_unlock:
	unlock_page(page);
	goto out_put;
}