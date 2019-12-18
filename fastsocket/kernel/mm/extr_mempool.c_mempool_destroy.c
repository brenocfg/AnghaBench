#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ curr_nr; scalar_t__ min_nr; } ;
typedef  TYPE_1__ mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  free_pool (TYPE_1__*) ; 

void mempool_destroy(mempool_t *pool)
{
	/* Check for outstanding elements */
	BUG_ON(pool->curr_nr != pool->min_nr);
	free_pool(pool);
}