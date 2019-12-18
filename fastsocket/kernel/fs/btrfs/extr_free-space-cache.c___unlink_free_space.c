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
struct btrfs_free_space_ctl {int /*<<< orphan*/  free_extents; int /*<<< orphan*/  free_space_offset; } ;
struct btrfs_free_space {int /*<<< orphan*/  offset_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
__unlink_free_space(struct btrfs_free_space_ctl *ctl,
		    struct btrfs_free_space *info)
{
	rb_erase(&info->offset_index, &ctl->free_space_offset);
	ctl->free_extents--;
}