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
struct qstr {int dummy; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct ext2_dir_entry_2 {int /*<<< orphan*/  inode; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 struct ext2_dir_entry_2* ext2_find_entry (struct inode*,struct qstr*,struct page**) ; 
 int /*<<< orphan*/  ext2_put_page (struct page*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

ino_t ext2_inode_by_name(struct inode *dir, struct qstr *child)
{
	ino_t res = 0;
	struct ext2_dir_entry_2 *de;
	struct page *page;
	
	de = ext2_find_entry (dir, child, &page);
	if (de) {
		res = le32_to_cpu(de->inode);
		ext2_put_page(page);
	}
	return res;
}