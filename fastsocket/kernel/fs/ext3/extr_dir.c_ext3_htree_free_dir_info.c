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
struct dir_private_info {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_rb_tree_fname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dir_private_info*) ; 

void ext3_htree_free_dir_info(struct dir_private_info *p)
{
	free_rb_tree_fname(&p->root);
	kfree(p);
}