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
struct btrfs_root {int dummy; } ;
struct btrfs_delayed_root {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_first_delayed_node (struct btrfs_delayed_root*) ; 
 struct btrfs_delayed_root* btrfs_get_delayed_root (struct btrfs_root*) ; 

void btrfs_assert_delayed_root_empty(struct btrfs_root *root)
{
	struct btrfs_delayed_root *delayed_root;
	delayed_root = btrfs_get_delayed_root(root);
	WARN_ON(btrfs_first_delayed_node(delayed_root));
}