#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stripe {TYPE_2__* sc; int /*<<< orphan*/  obj; } ;
struct dm_mem_cache_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cache; } ;
struct TYPE_4__ {TYPE_1__ kc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_mem_cache_free (struct dm_mem_cache_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_mem_cache_shrink (struct dm_mem_cache_client*,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct stripe*) ; 

__attribute__((used)) static void stripe_free(struct stripe *stripe, struct dm_mem_cache_client *mc)
{
	dm_mem_cache_free(mc, stripe->obj);
	dm_mem_cache_shrink(mc, 1);
	kmem_cache_free(stripe->sc->kc.cache, stripe);
}