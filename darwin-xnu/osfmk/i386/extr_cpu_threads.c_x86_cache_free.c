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
struct TYPE_4__ {int level; struct TYPE_4__* next; } ;
typedef  TYPE_1__ x86_cpu_cache_t ;

/* Variables and functions */
 int MAX_CACHE_DEPTH ; 
 int* num_Lx_caches ; 
 int num_caches ; 
 TYPE_1__* x86_caches ; 

__attribute__((used)) static void
x86_cache_free(x86_cpu_cache_t *cache)
{
    num_caches -= 1;
    if (cache->level > 0 && cache->level <= MAX_CACHE_DEPTH)
	num_Lx_caches[cache->level - 1] -= 1;
    cache->next = x86_caches;
    x86_caches = cache;
}