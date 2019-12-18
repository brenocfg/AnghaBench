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
typedef  int u32 ;
struct zfcp_unit {int /*<<< orphan*/  erp_counter; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ZFCP_SET ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  atomic_clear_mask (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_mask (int,int /*<<< orphan*/ *) ; 
 scalar_t__ status_change_clear (int,int /*<<< orphan*/ *) ; 
 scalar_t__ status_change_set (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_unit (char*,void*,struct zfcp_unit*) ; 

void zfcp_erp_modify_unit_status(struct zfcp_unit *unit, char *id, void *ref,
				 u32 mask, int set_or_clear)
{
	if (set_or_clear == ZFCP_SET) {
		if (status_change_set(mask, &unit->status))
			zfcp_dbf_rec_unit(id, ref, unit);
		atomic_set_mask(mask, &unit->status);
	} else {
		if (status_change_clear(mask, &unit->status))
			zfcp_dbf_rec_unit(id, ref, unit);
		atomic_clear_mask(mask, &unit->status);
		if (mask & ZFCP_STATUS_COMMON_ERP_FAILED) {
			atomic_set(&unit->erp_counter, 0);
		}
	}
}