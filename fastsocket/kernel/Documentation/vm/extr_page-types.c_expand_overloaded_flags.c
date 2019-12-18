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

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PRIVATE ; 
 int /*<<< orphan*/  READAHEAD ; 
 int /*<<< orphan*/  RECLAIM ; 
 int /*<<< orphan*/  SLAB ; 
 int /*<<< orphan*/  SLOB_FREE ; 
 int /*<<< orphan*/  SLUB_DEBUG ; 
 int /*<<< orphan*/  SLUB_FROZEN ; 
 int /*<<< orphan*/  WRITEBACK ; 

__attribute__((used)) static uint64_t expand_overloaded_flags(uint64_t flags)
{
	/* SLOB/SLUB overload several page flags */
	if (flags & BIT(SLAB)) {
		if (flags & BIT(PRIVATE))
			flags ^= BIT(PRIVATE) | BIT(SLOB_FREE);
		if (flags & BIT(ACTIVE))
			flags ^= BIT(ACTIVE) | BIT(SLUB_FROZEN);
		if (flags & BIT(ERROR))
			flags ^= BIT(ERROR) | BIT(SLUB_DEBUG);
	}

	/* PG_reclaim is overloaded as PG_readahead in the read path */
	if ((flags & (BIT(RECLAIM) | BIT(WRITEBACK))) == BIT(RECLAIM))
		flags ^= BIT(RECLAIM) | BIT(READAHEAD);

	return flags;
}