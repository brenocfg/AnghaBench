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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int block_write_begin (struct file*,struct address_space*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_get_block ; 
 int /*<<< orphan*/  nilfs_transaction_abort (int /*<<< orphan*/ ) ; 
 int nilfs_transaction_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_write_begin(struct file *file, struct address_space *mapping,
			     loff_t pos, unsigned len, unsigned flags,
			     struct page **pagep, void **fsdata)

{
	struct inode *inode = mapping->host;
	int err = nilfs_transaction_begin(inode->i_sb, NULL, 1);

	if (unlikely(err))
		return err;

	*pagep = NULL;
	err = block_write_begin(file, mapping, pos, len, flags, pagep,
				fsdata, nilfs_get_block);
	if (unlikely(err))
		nilfs_transaction_abort(inode->i_sb);
	return err;
}