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
struct ufs_dir_entry {int /*<<< orphan*/  d_ino; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  fs32_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ufs_dir_entry* ufs_find_entry (struct inode*,struct dentry*,struct page**) ; 
 int /*<<< orphan*/  ufs_put_page (struct page*) ; 

ino_t ufs_inode_by_name(struct inode *dir, struct dentry *dentry)
{
	ino_t res = 0;
	struct ufs_dir_entry *de;
	struct page *page;
	
	de = ufs_find_entry(dir, dentry, &page);
	if (de) {
		res = fs32_to_cpu(dir->i_sb, de->d_ino);
		ufs_put_page(page);
	}
	return res;
}