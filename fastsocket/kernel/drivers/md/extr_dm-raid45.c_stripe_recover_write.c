#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct stripe {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHUNK (struct stripe*,int) ; 
 int /*<<< orphan*/  DIRTY ; 
 int /*<<< orphan*/  chunk_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_xor (struct stripe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parity_xor (struct stripe*) ; 
 int stripe_chunks_rw (struct stripe*) ; 
 int /*<<< orphan*/  stripe_io_ref (struct stripe*) ; 
 int /*<<< orphan*/  stripe_zero_chunk (struct stripe*,int) ; 

__attribute__((used)) static int stripe_recover_write(struct stripe *stripe, int pi)
{
	BUG_ON(stripe_io_ref(stripe));

	/*
	 * If this is a reconstruct of a particular device, then
	 * reconstruct the respective chunk, else create parity chunk.
	 */
	if (pi > -1) {
		stripe_zero_chunk(stripe, pi);
		common_xor(stripe, stripe->io.size, 0, pi);
		chunk_set(CHUNK(stripe, pi), DIRTY);
	} else
		parity_xor(stripe);

	return stripe_chunks_rw(stripe);
}