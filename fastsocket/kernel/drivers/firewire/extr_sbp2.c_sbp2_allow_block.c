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
struct sbp2_logical_unit {TYPE_1__* tgt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dont_block; } ;

/* Variables and functions */

__attribute__((used)) static inline void sbp2_allow_block(struct sbp2_logical_unit *lu)
{
	/*
	 * We may access dont_block without taking card->lock here:
	 * All callers of sbp2_allow_block() and all callers of sbp2_unblock()
	 * are currently serialized against each other.
	 * And a wrong result in sbp2_conditionally_block()'s access of
	 * dont_block is rather harmless, it simply misses its first chance.
	 */
	--lu->tgt->dont_block;
}