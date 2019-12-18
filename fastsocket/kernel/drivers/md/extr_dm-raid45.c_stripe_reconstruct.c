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
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int recover; } ;
struct stripe {TYPE_1__ io; TYPE_3__ idx; int /*<<< orphan*/  sc; } ;
struct TYPE_5__ {int raid_devs; } ;
struct raid_set {scalar_t__ stats; TYPE_2__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CHUNK (struct stripe*,int) ; 
 int /*<<< orphan*/  ChunkUptodate (int /*<<< orphan*/ ) ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ RSDegraded (struct raid_set*) ; 
 scalar_t__ S_RECONSTRUCT_DEV ; 
 scalar_t__ S_RECONSTRUCT_EI ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int /*<<< orphan*/  common_xor (struct stripe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stripe_zero_chunk (struct stripe*,int) ; 

__attribute__((used)) static void stripe_reconstruct(struct stripe *stripe)
{
	struct raid_set *rs = RS(stripe->sc);
	int p = rs->set.raid_devs, pr = stripe->idx.recover;

	BUG_ON(pr < 0);

	/* Check if all but the chunk to be reconstructed are uptodate. */
	while (p--)
		BUG_ON(p != pr && !ChunkUptodate(CHUNK(stripe, p)));

	/* REMOVEME: statistics. */
	atomic_inc(rs->stats + (RSDegraded(rs) ? S_RECONSTRUCT_EI :
						 S_RECONSTRUCT_DEV));
	/* Zero chunk to be reconstructed. */
	stripe_zero_chunk(stripe, pr);
	common_xor(stripe, stripe->io.size, 0, pr);
}