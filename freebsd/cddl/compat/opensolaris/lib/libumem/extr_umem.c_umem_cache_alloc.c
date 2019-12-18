#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ (* constructor ) (void*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  callback_data; int /*<<< orphan*/  bufsize; } ;
typedef  TYPE_1__ umem_cache_t ;

/* Variables and functions */
 int UMEM_NOFAIL ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nofail_cb () ; 
 scalar_t__ stub1 (void*,int /*<<< orphan*/ ,int) ; 

void *umem_cache_alloc(umem_cache_t *cache, int flags)
{
	void *buf = malloc(cache->bufsize);
	if(buf == NULL) {
		if(!(flags & UMEM_NOFAIL))
			return NULL;

		if(nofail_cb != NULL)
			nofail_cb();
		abort();
	}

	if(cache->constructor != NULL) {
		if(cache->constructor(buf, cache->callback_data, flags) != 0) {
			free(buf);
			if(!(flags & UMEM_NOFAIL))
				return NULL;

			if(nofail_cb != NULL)
				nofail_cb();
			abort();
		}
	}

	return buf;
}