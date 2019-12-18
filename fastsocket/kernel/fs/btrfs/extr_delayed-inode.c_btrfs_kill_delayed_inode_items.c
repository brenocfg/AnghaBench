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
struct inode {int dummy; } ;
struct btrfs_delayed_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __btrfs_kill_delayed_node (struct btrfs_delayed_node*) ; 
 struct btrfs_delayed_node* btrfs_get_delayed_node (struct inode*) ; 
 int /*<<< orphan*/  btrfs_release_delayed_node (struct btrfs_delayed_node*) ; 

void btrfs_kill_delayed_inode_items(struct inode *inode)
{
	struct btrfs_delayed_node *delayed_node;

	delayed_node = btrfs_get_delayed_node(inode);
	if (!delayed_node)
		return;

	__btrfs_kill_delayed_node(delayed_node);
	btrfs_release_delayed_node(delayed_node);
}