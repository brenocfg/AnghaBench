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
struct bool_gen {unsigned int* seed; int /*<<< orphan*/  lock; scalar_t__ state; } ;

/* Variables and functions */
 int RANDOM_BOOL_GEN_SEED_COUNT ; 
 scalar_t__ early_random () ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
random_bool_init(struct bool_gen * bg)
{
	/* Seed the random boolean generator */
	for (int i = 0; i < RANDOM_BOOL_GEN_SEED_COUNT; i++) {
		bg->seed[i] = (unsigned int)early_random();
	}
	bg->state = 0;
	simple_lock_init(&bg->lock, 0);
}