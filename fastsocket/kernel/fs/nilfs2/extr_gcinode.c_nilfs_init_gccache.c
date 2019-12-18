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
struct the_nilfs {int /*<<< orphan*/ * ns_gc_inodes_h; int /*<<< orphan*/  ns_gc_inodes; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NILFS_GCINODE_HASH_SIZE ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

int nilfs_init_gccache(struct the_nilfs *nilfs)
{
	int loop;

	BUG_ON(nilfs->ns_gc_inodes_h);

	INIT_LIST_HEAD(&nilfs->ns_gc_inodes);

	nilfs->ns_gc_inodes_h =
		kmalloc(sizeof(struct hlist_head) * NILFS_GCINODE_HASH_SIZE,
			GFP_NOFS);
	if (nilfs->ns_gc_inodes_h == NULL)
		return -ENOMEM;

	for (loop = 0; loop < NILFS_GCINODE_HASH_SIZE; loop++)
		INIT_HLIST_HEAD(&nilfs->ns_gc_inodes_h[loop]);
	return 0;
}