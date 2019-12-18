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
struct page {int dummy; } ;
struct inode {struct address_space* i_mapping; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {struct inode* d_inode; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct page* read_mapping_page (struct address_space*,int /*<<< orphan*/ ,void*) ; 

struct page *ecryptfs_get_locked_page(struct file *file, loff_t index)
{
	struct dentry *dentry;
	struct inode *inode;
	struct address_space *mapping;
	struct page *page;

	dentry = file->f_path.dentry;
	inode = dentry->d_inode;
	mapping = inode->i_mapping;
	page = read_mapping_page(mapping, index, (void *)file);
	if (!IS_ERR(page))
		lock_page(page);
	return page;
}