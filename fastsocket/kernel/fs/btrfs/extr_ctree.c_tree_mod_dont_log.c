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
struct extent_buffer {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_mod_seq_list; } ;

/* Variables and functions */
 scalar_t__ btrfs_header_level (struct extent_buffer*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static inline int tree_mod_dont_log(struct btrfs_fs_info *fs_info,
				    struct extent_buffer *eb) {
	smp_mb();
	if (list_empty(&(fs_info)->tree_mod_seq_list))
		return 1;
	if (!eb)
		return 0;
	if (btrfs_header_level(eb) == 0)
		return 1;
	return 0;
}