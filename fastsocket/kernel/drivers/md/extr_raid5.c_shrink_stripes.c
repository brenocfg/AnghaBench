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
struct r5conf {int /*<<< orphan*/ * slab_cache; } ;

/* Variables and functions */
 scalar_t__ drop_one_stripe (struct r5conf*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shrink_stripes(struct r5conf *conf)
{
	while (drop_one_stripe(conf))
		;

	if (conf->slab_cache)
		kmem_cache_destroy(conf->slab_cache);
	conf->slab_cache = NULL;
}