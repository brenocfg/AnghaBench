#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_5__ {scalar_t__ target_identifier; } ;
struct TYPE_6__ {scalar_t__ target_identifier; TYPE_1__ valid; int /*<<< orphan*/  check_info; } ;
typedef  TYPE_2__ sal_log_mod_error_info_t ;
typedef  int /*<<< orphan*/  peidx_table_t ;
struct TYPE_7__ {int level; } ;
typedef  TYPE_3__ pal_cache_check_info_t ;

/* Variables and functions */
 TYPE_2__* peidx_bus_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ peidx_cache_check (int /*<<< orphan*/ *,int) ; 
 int peidx_cache_check_num (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64
get_target_identifier(peidx_table_t *peidx)
{
	u64 target_address = 0;
	sal_log_mod_error_info_t *smei;
	pal_cache_check_info_t *pcci;
	int i, level = 9;

	/*
	 * Look through the cache checks for a valid target identifier
	 * If more than one valid target identifier, return the one
	 * with the lowest cache level.
	 */
	for (i = 0; i < peidx_cache_check_num(peidx); i++) {
		smei = (sal_log_mod_error_info_t *)peidx_cache_check(peidx, i);
		if (smei->valid.target_identifier && smei->target_identifier) {
			pcci = (pal_cache_check_info_t *)&(smei->check_info);
			if (!target_address || (pcci->level < level)) {
				target_address = smei->target_identifier;
				level = pcci->level;
				continue;
			}
		}
	}
	if (target_address)
		return target_address;

	/*
	 * Look at the bus check for a valid target identifier
	 */
	smei = peidx_bus_check(peidx, 0);
	if (smei && smei->valid.target_identifier)
		return smei->target_identifier;

	return 0;
}