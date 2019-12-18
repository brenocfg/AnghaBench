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
typedef  int /*<<< orphan*/  u32 ;
struct ghes_estatus_cache {int /*<<< orphan*/  time_in; struct acpi_hest_generic* generic; int /*<<< orphan*/  count; int /*<<< orphan*/  estatus_len; } ;
struct acpi_hest_generic_status {int dummy; } ;
struct acpi_hest_generic {int dummy; } ;

/* Variables and functions */
 int GHES_ESTATUS_CACHE_ALLOCED_MAX ; 
 int /*<<< orphan*/  GHES_ESTATUS_CACHE_LEN (int /*<<< orphan*/ ) ; 
 struct acpi_hest_generic_status* GHES_ESTATUS_FROM_CACHE (struct ghes_estatus_cache*) ; 
 int /*<<< orphan*/  apei_estatus_len (struct acpi_hest_generic_status*) ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghes_estatus_cache_alloced ; 
 int /*<<< orphan*/  ghes_estatus_pool ; 
 int /*<<< orphan*/  memcpy (struct acpi_hest_generic_status*,struct acpi_hest_generic_status*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_clock () ; 

__attribute__((used)) static struct ghes_estatus_cache *ghes_estatus_cache_alloc(
	struct acpi_hest_generic *generic,
	struct acpi_hest_generic_status *estatus)
{
	int alloced;
	u32 len, cache_len;
	struct ghes_estatus_cache *cache;
	struct acpi_hest_generic_status *cache_estatus;

	alloced = atomic_add_return(1, &ghes_estatus_cache_alloced);
	if (alloced > GHES_ESTATUS_CACHE_ALLOCED_MAX) {
		atomic_dec(&ghes_estatus_cache_alloced);
		return NULL;
	}
	len = apei_estatus_len(estatus);
	cache_len = GHES_ESTATUS_CACHE_LEN(len);
	cache = (void *)gen_pool_alloc(ghes_estatus_pool, cache_len);
	if (!cache) {
		atomic_dec(&ghes_estatus_cache_alloced);
		return NULL;
	}
	cache_estatus = GHES_ESTATUS_FROM_CACHE(cache);
	memcpy(cache_estatus, estatus, len);
	cache->estatus_len = len;
	atomic_set(&cache->count, 0);
	cache->generic = generic;
	cache->time_in = sched_clock();
	return cache;
}