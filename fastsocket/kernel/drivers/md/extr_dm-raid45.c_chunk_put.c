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
struct stripe_chunk {int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chunk_put(struct stripe_chunk *chunk)
{
	BUG_ON(atomic_dec_return(&chunk->cnt) < 0);
}