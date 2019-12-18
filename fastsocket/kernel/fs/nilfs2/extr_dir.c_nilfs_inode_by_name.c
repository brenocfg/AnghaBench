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
struct page {int dummy; } ;
struct nilfs_dir_entry {int /*<<< orphan*/  inode; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct nilfs_dir_entry* nilfs_find_entry (struct inode*,struct dentry*,struct page**) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 

ino_t nilfs_inode_by_name(struct inode *dir, struct dentry *dentry)
{
	ino_t res = 0;
	struct nilfs_dir_entry *de;
	struct page *page;

	de = nilfs_find_entry(dir, dentry, &page);
	if (de) {
		res = le64_to_cpu(de->inode);
		kunmap(page);
		page_cache_release(page);
	}
	return res;
}