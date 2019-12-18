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
struct TYPE_2__ {int seeks; int /*<<< orphan*/ * shrink; } ;
struct ttm_pool_manager {TYPE_1__ mm_shrink; } ;

/* Variables and functions */
 int /*<<< orphan*/  register_shrinker (TYPE_1__*) ; 
 int /*<<< orphan*/  ttm_pool_mm_shrink ; 

__attribute__((used)) static void ttm_pool_mm_shrink_init(struct ttm_pool_manager *manager)
{
	manager->mm_shrink.shrink = &ttm_pool_mm_shrink;
	manager->mm_shrink.seeks = 1;
	register_shrinker(&manager->mm_shrink);
}