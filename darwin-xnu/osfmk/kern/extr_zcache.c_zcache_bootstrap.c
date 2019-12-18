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
typedef  int /*<<< orphan*/  uint16_t ;
struct zcc_magazine {int dummy; } ;

/* Variables and functions */
 int DEFAULT_DEPOT_SIZE ; 
 int DEFAULT_MAGAZINE_SIZE ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  PE_parse_boot_argn (char*,int*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int depot_element_count ; 
 scalar_t__ early_random () ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int magazine_element_count ; 
 int /*<<< orphan*/ * magazine_zone ; 
 uintptr_t zcache_canary ; 
 int /*<<< orphan*/  zcache_init_marked_zones () ; 
 int /*<<< orphan*/  zcache_locks_grp ; 
 int /*<<< orphan*/ * zinit (int,int,int,char*) ; 
 int /*<<< orphan*/  zone_cache_ready ; 

void zcache_bootstrap(void)
{
	/* use boot-arg for custom magazine size*/
	if (! PE_parse_boot_argn("zcc_magazine_element_count", &magazine_element_count, sizeof (uint16_t)))
		magazine_element_count = DEFAULT_MAGAZINE_SIZE;

	int magazine_size = sizeof(struct zcc_magazine) + magazine_element_count * sizeof(void *);

	magazine_zone = zinit(magazine_size, 100000 * magazine_size , magazine_size, "zcc_magazine_zone");

	assert(magazine_zone != NULL);

	/* use boot-arg for custom depot size*/
	if (! PE_parse_boot_argn("zcc_depot_element_count", &depot_element_count, sizeof (uint16_t)))
		depot_element_count = DEFAULT_DEPOT_SIZE;

	lck_grp_init(&zcache_locks_grp, "zcc_depot_lock", LCK_GRP_ATTR_NULL);

	/* Generate the canary value for zone caches */
	zcache_canary = (uintptr_t) early_random();

	zone_cache_ready = TRUE;

	zcache_init_marked_zones();
}