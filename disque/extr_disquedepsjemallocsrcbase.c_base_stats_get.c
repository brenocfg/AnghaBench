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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t base_allocated ; 
 size_t base_mapped ; 
 int /*<<< orphan*/  base_mtx ; 
 size_t base_resident ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
base_stats_get(size_t *allocated, size_t *resident, size_t *mapped)
{

	malloc_mutex_lock(&base_mtx);
	assert(base_allocated <= base_resident);
	assert(base_resident <= base_mapped);
	*allocated = base_allocated;
	*resident = base_resident;
	*mapped = base_mapped;
	malloc_mutex_unlock(&base_mtx);
}