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
struct exofs_dir_entry {int /*<<< orphan*/  inode_no; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 struct exofs_dir_entry* exofs_dotdot (int /*<<< orphan*/ ,struct page**) ; 
 int /*<<< orphan*/  exofs_put_page (struct page*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

ino_t exofs_parent_ino(struct dentry *child)
{
	struct page *page;
	struct exofs_dir_entry *de;
	ino_t ino;

	de = exofs_dotdot(child->d_inode, &page);
	if (!de)
		return 0;

	ino = le64_to_cpu(de->inode_no);
	exofs_put_page(page);
	return ino;
}