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
struct extent_buffer {int dummy; } ;
struct btrfs_chunk {int dummy; } ;
struct btrfs_balance_args {scalar_t__ vend; scalar_t__ vstart; } ;

/* Variables and functions */
 scalar_t__ btrfs_chunk_length (struct extent_buffer*,struct btrfs_chunk*) ; 

__attribute__((used)) static int chunk_vrange_filter(struct extent_buffer *leaf,
			       struct btrfs_chunk *chunk,
			       u64 chunk_offset,
			       struct btrfs_balance_args *bargs)
{
	if (chunk_offset < bargs->vend &&
	    chunk_offset + btrfs_chunk_length(leaf, chunk) > bargs->vstart)
		/* at least part of the chunk is inside this vrange */
		return 0;

	return 1;
}