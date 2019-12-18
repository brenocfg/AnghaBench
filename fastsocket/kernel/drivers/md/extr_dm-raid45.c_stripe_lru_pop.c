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
struct stripe_cache {int dummy; } ;
struct stripe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_LRU ; 
 int /*<<< orphan*/  POP_LIST (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct stripe *stripe_lru_pop(struct stripe_cache *sc)
{
	struct stripe *stripe;

	POP_LIST(LIST_LRU);
	return stripe;
}