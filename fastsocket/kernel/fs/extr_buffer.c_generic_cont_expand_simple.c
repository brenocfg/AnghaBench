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
struct inode {struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int AOP_FLAG_CONT_EXPAND ; 
 int AOP_FLAG_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int inode_newsize_ok (struct inode*,int /*<<< orphan*/ ) ; 
 int pagecache_write_begin (int /*<<< orphan*/ *,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct page**,void**) ; 
 int pagecache_write_end (int /*<<< orphan*/ *,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*,void*) ; 

int generic_cont_expand_simple(struct inode *inode, loff_t size)
{
	struct address_space *mapping = inode->i_mapping;
	struct page *page;
	void *fsdata;
	int err;

	err = inode_newsize_ok(inode, size);
	if (err)
		goto out;

	err = pagecache_write_begin(NULL, mapping, size, 0,
				AOP_FLAG_UNINTERRUPTIBLE|AOP_FLAG_CONT_EXPAND,
				&page, &fsdata);
	if (err)
		goto out;

	err = pagecache_write_end(NULL, mapping, size, 0, 0, page, fsdata);
	BUG_ON(err > 0);

out:
	return err;
}