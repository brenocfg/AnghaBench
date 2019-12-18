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
typedef  scalar_t__ u64 ;
struct btrfs_free_space_ctl {int /*<<< orphan*/  free_space; } ;
struct btrfs_free_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bitmap_clear_bits (struct btrfs_free_space_ctl*,struct btrfs_free_space*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void bitmap_clear_bits(struct btrfs_free_space_ctl *ctl,
			      struct btrfs_free_space *info, u64 offset,
			      u64 bytes)
{
	__bitmap_clear_bits(ctl, info, offset, bytes);
	ctl->free_space -= bytes;
}