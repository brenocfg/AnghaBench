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
struct ghes_estatus_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GHES_ESTATUS_CACHE_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GHES_ESTATUS_FROM_CACHE (struct ghes_estatus_cache*) ; 
 int /*<<< orphan*/  apei_estatus_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghes_estatus_cache_alloced ; 
 int /*<<< orphan*/  ghes_estatus_pool ; 

__attribute__((used)) static void ghes_estatus_cache_free(struct ghes_estatus_cache *cache)
{
	u32 len;

	len = apei_estatus_len(GHES_ESTATUS_FROM_CACHE(cache));
	len = GHES_ESTATUS_CACHE_LEN(len);
	gen_pool_free(ghes_estatus_pool, (unsigned long)cache, len);
	atomic_dec(&ghes_estatus_cache_alloced);
}