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
struct the_nilfs {int /*<<< orphan*/ * ns_gc_inodes_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_remove_all_gcinode (struct the_nilfs*) ; 

void nilfs_destroy_gccache(struct the_nilfs *nilfs)
{
	if (nilfs->ns_gc_inodes_h) {
		nilfs_remove_all_gcinode(nilfs);
		kfree(nilfs->ns_gc_inodes_h);
		nilfs->ns_gc_inodes_h = NULL;
	}
}