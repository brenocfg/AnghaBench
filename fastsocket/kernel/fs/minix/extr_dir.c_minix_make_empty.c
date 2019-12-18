#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct minix_sb_info {int s_dirsize; scalar_t__ s_version; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  inode; } ;
typedef  TYPE_1__ minix_dirent ;
typedef  TYPE_1__ minix3_dirent ;

/* Variables and functions */
 int /*<<< orphan*/  AOP_FLAG_UNINTERRUPTIBLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_USER0 ; 
 scalar_t__ MINIX_V3 ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int __minix_write_begin (int /*<<< orphan*/ *,struct address_space*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 int dir_commit_chunk (struct page*,int /*<<< orphan*/ ,int) ; 
 struct page* grab_cache_page (struct address_space*,int /*<<< orphan*/ ) ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* minix_next_entry (TYPE_1__*,struct minix_sb_info*) ; 
 struct minix_sb_info* minix_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int minix_make_empty(struct inode *inode, struct inode *dir)
{
	struct address_space *mapping = inode->i_mapping;
	struct page *page = grab_cache_page(mapping, 0);
	struct minix_sb_info *sbi = minix_sb(inode->i_sb);
	char *kaddr;
	int err;

	if (!page)
		return -ENOMEM;
	err = __minix_write_begin(NULL, mapping, 0, 2 * sbi->s_dirsize,
					AOP_FLAG_UNINTERRUPTIBLE, &page, NULL);
	if (err) {
		unlock_page(page);
		goto fail;
	}

	kaddr = kmap_atomic(page, KM_USER0);
	memset(kaddr, 0, PAGE_CACHE_SIZE);

	if (sbi->s_version == MINIX_V3) {
		minix3_dirent *de3 = (minix3_dirent *)kaddr;

		de3->inode = inode->i_ino;
		strcpy(de3->name, ".");
		de3 = minix_next_entry(de3, sbi);
		de3->inode = dir->i_ino;
		strcpy(de3->name, "..");
	} else {
		minix_dirent *de = (minix_dirent *)kaddr;

		de->inode = inode->i_ino;
		strcpy(de->name, ".");
		de = minix_next_entry(de, sbi);
		de->inode = dir->i_ino;
		strcpy(de->name, "..");
	}
	kunmap_atomic(kaddr, KM_USER0);

	err = dir_commit_chunk(page, 0, 2 * sbi->s_dirsize);
fail:
	page_cache_release(page);
	return err;
}