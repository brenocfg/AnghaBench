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
typedef  int /*<<< orphan*/  umem_reclaim_t ;
typedef  int /*<<< orphan*/  umem_destructor_t ;
typedef  int /*<<< orphan*/  umem_constructor_t ;
struct TYPE_4__ {size_t bufsize; void* callback_data; int /*<<< orphan*/ * destructor; int /*<<< orphan*/ * constructor; } ;
typedef  TYPE_1__ umem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 

umem_cache_t *umem_cache_create(char *debug_name, size_t bufsize, size_t align, umem_constructor_t *constructor, umem_destructor_t *destructor, umem_reclaim_t *reclaim, void *callback_data, void *source, int cflags)
{
	assert(source == NULL);

	umem_cache_t *cache = malloc(sizeof(umem_cache_t));
	if(cache == NULL)
		return NULL;

	cache->constructor = constructor;
	cache->destructor = destructor;
	cache->callback_data = callback_data;
	cache->bufsize = bufsize;

	return cache;
}