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
struct seq_list {int /*<<< orphan*/  list; int /*<<< orphan*/  seq; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_mod_seq_list; int /*<<< orphan*/  tree_mod_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
__get_tree_mod_seq(struct btrfs_fs_info *fs_info, struct seq_list *elem)
{
	elem->seq = atomic_inc_return(&fs_info->tree_mod_seq);
	list_add_tail(&elem->list, &fs_info->tree_mod_seq_list);
}