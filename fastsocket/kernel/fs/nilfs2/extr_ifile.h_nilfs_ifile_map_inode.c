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
struct nilfs_inode {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 void* kmap (int /*<<< orphan*/ ) ; 
 struct nilfs_inode* nilfs_palloc_block_get_entry (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,void*) ; 

__attribute__((used)) static inline struct nilfs_inode *
nilfs_ifile_map_inode(struct inode *ifile, ino_t ino, struct buffer_head *ibh)
{
	void *kaddr = kmap(ibh->b_page);
	return nilfs_palloc_block_get_entry(ifile, ino, ibh, kaddr);
}