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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct dm_cell_key {unsigned long const block; } ;
struct dm_bio_prison {int hash_mask; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t hash_key(struct dm_bio_prison *prison, struct dm_cell_key *key)
{
	const unsigned long BIG_PRIME = 4294967291UL;
	uint64_t hash = key->block * BIG_PRIME;

	return (uint32_t) (hash & prison->hash_mask);
}