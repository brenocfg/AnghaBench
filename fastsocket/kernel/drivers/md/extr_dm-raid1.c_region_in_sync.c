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
struct mirror_set {int /*<<< orphan*/  rh; } ;
typedef  int /*<<< orphan*/  region_t ;

/* Variables and functions */
 int DM_RH_CLEAN ; 
 int DM_RH_DIRTY ; 
 int dm_rh_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int region_in_sync(struct mirror_set *ms, region_t region,
				 int may_block)
{
	int state = dm_rh_get_state(ms->rh, region, may_block);
	return state == DM_RH_CLEAN || state == DM_RH_DIRTY;
}