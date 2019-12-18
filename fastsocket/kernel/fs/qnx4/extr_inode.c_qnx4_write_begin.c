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
struct qnx4_inode_info {int /*<<< orphan*/  mmu_private; } ;
struct page {int dummy; } ;
struct file {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int cont_write_begin (struct file*,struct address_space*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page**,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qnx4_get_block ; 
 struct qnx4_inode_info* qnx4_i (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qnx4_write_begin(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned flags,
			struct page **pagep, void **fsdata)
{
	struct qnx4_inode_info *qnx4_inode = qnx4_i(mapping->host);
	*pagep = NULL;
	return cont_write_begin(file, mapping, pos, len, flags, pagep, fsdata,
				qnx4_get_block,
				&qnx4_inode->mmu_private);
}