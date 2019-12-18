#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parity; } ;
struct TYPE_4__ {unsigned int size; } ;
struct stripe {TYPE_3__ idx; int /*<<< orphan*/  key; TYPE_1__ io; int /*<<< orphan*/  sc; } ;
struct TYPE_5__ {unsigned int io_size; unsigned int chunk_size; int data_devs; } ;
struct raid_set {TYPE_2__ set; } ;
struct raid_address {int /*<<< orphan*/  pi; } ;
typedef  unsigned int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK (struct stripe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIRTY ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_xor (struct stripe*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid_address (struct raid_set*,int,struct raid_address*) ; 
 int /*<<< orphan*/  stripe_zero_pl_part (struct stripe*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void parity_xor(struct stripe *stripe)
{
	struct raid_set *rs = RS(stripe->sc);
	int size_differs = stripe->io.size != rs->set.io_size;
	unsigned chunk_size = rs->set.chunk_size, io_size = stripe->io.size,
		 xor_size = chunk_size > io_size ? io_size : chunk_size;
	sector_t off;

	/* This can be the recover stripe with a larger io size. */
	for (off = 0; off < io_size; off += xor_size) {
		/*
		 * Recover stripe is likely bigger than regular io
		 * ones and has no precalculated parity disk index ->
		 * need to calculate RAID address.
		 */
		if (unlikely(size_differs)) {
			struct raid_address addr;

			raid_address(rs, (stripe->key + off) *
					 rs->set.data_devs, &addr);
			stripe->idx.parity = addr.pi;
			stripe_zero_pl_part(stripe, addr.pi, off, xor_size);
		}

		common_xor(stripe, xor_size, off, stripe->idx.parity);
		chunk_set(CHUNK(stripe, stripe->idx.parity), DIRTY);
	}
}