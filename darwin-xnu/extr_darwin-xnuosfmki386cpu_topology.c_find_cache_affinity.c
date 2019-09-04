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
typedef  int /*<<< orphan*/  x86_cpu_cache_t ;
struct TYPE_4__ {int /*<<< orphan*/ * cache; struct TYPE_4__* next; } ;
typedef  TYPE_1__ x86_affinity_set_t ;

/* Variables and functions */
 TYPE_1__* x86_affinities ; 

__attribute__((used)) static x86_affinity_set_t *
find_cache_affinity(x86_cpu_cache_t *l2_cachep)
{
	x86_affinity_set_t	*aset;

	for (aset = x86_affinities; aset != NULL; aset = aset->next) {
		if (l2_cachep == aset->cache)
			break;
	}
	return aset;			
}