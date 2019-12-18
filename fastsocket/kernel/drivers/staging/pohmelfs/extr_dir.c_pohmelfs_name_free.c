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
struct pohmelfs_name {int /*<<< orphan*/  sync_create_entry; } ;
struct pohmelfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pohmelfs_name_del (struct pohmelfs_inode*,struct pohmelfs_name*) ; 
 int /*<<< orphan*/  kfree (struct pohmelfs_name*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pohmelfs_name_free(struct pohmelfs_inode *parent, struct pohmelfs_name *node)
{
	__pohmelfs_name_del(parent, node);
	list_del(&node->sync_create_entry);
	kfree(node);
}