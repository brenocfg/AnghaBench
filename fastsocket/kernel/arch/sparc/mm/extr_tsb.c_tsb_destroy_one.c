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
struct tsb_config {int tsb_reg_val; int /*<<< orphan*/ * tsb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsb_caches ; 

__attribute__((used)) static void tsb_destroy_one(struct tsb_config *tp)
{
	unsigned long cache_index;

	if (!tp->tsb)
		return;
	cache_index = tp->tsb_reg_val & 0x7UL;
	kmem_cache_free(tsb_caches[cache_index], tp->tsb);
	tp->tsb = NULL;
	tp->tsb_reg_val = 0UL;
}