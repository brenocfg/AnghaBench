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
struct pohmelfs_name {int /*<<< orphan*/  hash_node; } ;
struct pohmelfs_inode {int /*<<< orphan*/  hash_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __pohmelfs_name_del(struct pohmelfs_inode *parent, struct pohmelfs_name *node)
{
	rb_erase(&node->hash_node, &parent->hash_root);
}