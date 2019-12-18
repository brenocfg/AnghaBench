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
struct sysv_dir_entry {int /*<<< orphan*/  name; void* inode; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOP_FLAG_UNINTERRUPTIBLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int SYSV_DIRSIZE ; 
 int /*<<< orphan*/  SYSV_SB (int /*<<< orphan*/ ) ; 
 int __sysv_write_begin (int /*<<< orphan*/ *,struct address_space*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 void* cpu_to_fs16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dir_commit_chunk (struct page*,int /*<<< orphan*/ ,int) ; 
 struct page* grab_cache_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int sysv_make_empty(struct inode *inode, struct inode *dir)
{
	struct address_space *mapping = inode->i_mapping;
	struct page *page = grab_cache_page(mapping, 0);
	struct sysv_dir_entry * de;
	char *base;
	int err;

	if (!page)
		return -ENOMEM;
	err = __sysv_write_begin(NULL, mapping, 0, 2 * SYSV_DIRSIZE,
				AOP_FLAG_UNINTERRUPTIBLE, &page, NULL);
	if (err) {
		unlock_page(page);
		goto fail;
	}
	kmap(page);

	base = (char*)page_address(page);
	memset(base, 0, PAGE_CACHE_SIZE);

	de = (struct sysv_dir_entry *) base;
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	strcpy(de->name,".");
	de++;
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), dir->i_ino);
	strcpy(de->name,"..");

	kunmap(page);
	err = dir_commit_chunk(page, 0, 2 * SYSV_DIRSIZE);
fail:
	page_cache_release(page);
	return err;
}