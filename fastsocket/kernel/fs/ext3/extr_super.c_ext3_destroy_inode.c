#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct ext3_inode_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_orphan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 TYPE_1__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ext3_inode_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  printk (char*,TYPE_1__*) ; 

__attribute__((used)) static void ext3_destroy_inode(struct inode *inode)
{
	if (!list_empty(&(EXT3_I(inode)->i_orphan))) {
		printk("EXT3 Inode %p: orphan list check failed!\n",
			EXT3_I(inode));
		print_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS, 16, 4,
				EXT3_I(inode), sizeof(struct ext3_inode_info),
				false);
		dump_stack();
	}
	kmem_cache_free(ext3_inode_cachep, EXT3_I(inode));
}