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
struct btrfs_stripe {int dummy; } ;
struct btrfs_chunk {int dummy; } ;
struct btrfs_balance_args {int flags; scalar_t__ devid; scalar_t__ pend; scalar_t__ pstart; } ;

/* Variables and functions */
 int BTRFS_BALANCE_ARGS_DEVID ; 
 int BTRFS_BLOCK_GROUP_DUP ; 
 int BTRFS_BLOCK_GROUP_RAID1 ; 
 int BTRFS_BLOCK_GROUP_RAID10 ; 
 scalar_t__ btrfs_chunk_length (struct extent_buffer*,struct btrfs_chunk*) ; 
 int btrfs_chunk_num_stripes (struct extent_buffer*,struct btrfs_chunk*) ; 
 int btrfs_chunk_type (struct extent_buffer*,struct btrfs_chunk*) ; 
 scalar_t__ btrfs_stripe_devid (struct extent_buffer*,struct btrfs_stripe*) ; 
 struct btrfs_stripe* btrfs_stripe_nr (struct btrfs_chunk*,int) ; 
 scalar_t__ btrfs_stripe_offset (struct extent_buffer*,struct btrfs_stripe*) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int) ; 

__attribute__((used)) static int chunk_drange_filter(struct extent_buffer *leaf,
			       struct btrfs_chunk *chunk,
			       u64 chunk_offset,
			       struct btrfs_balance_args *bargs)
{
	struct btrfs_stripe *stripe;
	int num_stripes = btrfs_chunk_num_stripes(leaf, chunk);
	u64 stripe_offset;
	u64 stripe_length;
	int factor;
	int i;

	if (!(bargs->flags & BTRFS_BALANCE_ARGS_DEVID))
		return 0;

	if (btrfs_chunk_type(leaf, chunk) & (BTRFS_BLOCK_GROUP_DUP |
	     BTRFS_BLOCK_GROUP_RAID1 | BTRFS_BLOCK_GROUP_RAID10))
		factor = 2;
	else
		factor = 1;
	factor = num_stripes / factor;

	for (i = 0; i < num_stripes; i++) {
		stripe = btrfs_stripe_nr(chunk, i);
		if (btrfs_stripe_devid(leaf, stripe) != bargs->devid)
			continue;

		stripe_offset = btrfs_stripe_offset(leaf, stripe);
		stripe_length = btrfs_chunk_length(leaf, chunk);
		do_div(stripe_length, factor);

		if (stripe_offset < bargs->pend &&
		    stripe_offset + stripe_length > bargs->pstart)
			return 0;
	}

	return 1;
}