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
struct btrfs_free_space_ctl {int /*<<< orphan*/  free_space; int /*<<< orphan*/  unit; } ;
struct btrfs_free_space {int /*<<< orphan*/  bytes; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 unsigned long BITS_PER_BITMAP ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long bytes_to_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long offset_to_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bitmap_set_bits(struct btrfs_free_space_ctl *ctl,
			    struct btrfs_free_space *info, u64 offset,
			    u64 bytes)
{
	unsigned long start, count;

	start = offset_to_bit(info->offset, ctl->unit, offset);
	count = bytes_to_bits(bytes, ctl->unit);
	BUG_ON(start + count > BITS_PER_BITMAP);

	bitmap_set(info->bitmap, start, count);

	info->bytes += bytes;
	ctl->free_space += bytes;
}