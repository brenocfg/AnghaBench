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
struct TYPE_3__ {int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* destructor ) (void*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ umem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 

void umem_cache_free(umem_cache_t *cache, void *buffer)
{
	if(cache->destructor != NULL)
		cache->destructor(buffer, cache->callback_data);

	free(buffer);
}