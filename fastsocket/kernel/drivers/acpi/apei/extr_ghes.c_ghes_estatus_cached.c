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
typedef  scalar_t__ u32 ;
struct ghes_estatus_cache {scalar_t__ estatus_len; unsigned long long time_in; int /*<<< orphan*/  count; } ;
struct acpi_hest_generic_status {int dummy; } ;

/* Variables and functions */
 int GHES_ESTATUS_CACHES_SIZE ; 
 struct acpi_hest_generic_status* GHES_ESTATUS_FROM_CACHE (struct ghes_estatus_cache*) ; 
 unsigned long long GHES_ESTATUS_IN_CACHE_MAX_NSEC ; 
 scalar_t__ apei_estatus_len (struct acpi_hest_generic_status*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghes_estatus_caches ; 
 scalar_t__ memcmp (struct acpi_hest_generic_status*,struct acpi_hest_generic_status*,scalar_t__) ; 
 struct ghes_estatus_cache* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned long long sched_clock () ; 

__attribute__((used)) static int ghes_estatus_cached(struct acpi_hest_generic_status *estatus)
{
	u32 len;
	int i, cached = 0;
	unsigned long long now;
	struct ghes_estatus_cache *cache;
	struct acpi_hest_generic_status *cache_estatus;

	len = apei_estatus_len(estatus);
	rcu_read_lock();
	for (i = 0; i < GHES_ESTATUS_CACHES_SIZE; i++) {
		cache = rcu_dereference(ghes_estatus_caches[i]);
		if (cache == NULL)
			continue;
		if (len != cache->estatus_len)
			continue;
		cache_estatus = GHES_ESTATUS_FROM_CACHE(cache);
		if (memcmp(estatus, cache_estatus, len))
			continue;
		atomic_inc(&cache->count);
		now = sched_clock();
		if (now - cache->time_in < GHES_ESTATUS_IN_CACHE_MAX_NSEC)
			cached = 1;
		break;
	}
	rcu_read_unlock();
	return cached;
}