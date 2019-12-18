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
struct btrfs_delayed_ref_node {int is_head; } ;

/* Variables and functions */

__attribute__((used)) static int btrfs_delayed_ref_is_head(struct btrfs_delayed_ref_node *node)
{
	return node->is_head;
}