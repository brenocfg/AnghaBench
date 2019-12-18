#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__** caches; } ;
typedef  TYPE_1__ x86_lcpu_t ;
struct TYPE_6__ {int level; int nlcpus; TYPE_1__** cpus; struct TYPE_6__* next; } ;
typedef  TYPE_2__ x86_cpu_cache_t ;

/* Variables and functions */

__attribute__((used)) static void
x86_cache_add_lcpu(x86_cpu_cache_t *cache, x86_lcpu_t *lcpu)
{
    x86_cpu_cache_t	*cur_cache;
    int			i;

    /*
     * Put the new CPU into the list of the cache.
     */
    cur_cache = lcpu->caches[cache->level - 1];
    lcpu->caches[cache->level - 1] = cache;
    cache->next = cur_cache;
    cache->nlcpus += 1;
    for (i = 0; i < cache->nlcpus; i += 1) {
	if (cache->cpus[i] == NULL) {
	    cache->cpus[i] = lcpu;
	    break;
	}
    }
}