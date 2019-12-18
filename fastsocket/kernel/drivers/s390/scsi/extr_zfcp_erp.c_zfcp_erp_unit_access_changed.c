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
struct zfcp_unit {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ZFCP_STATUS_COMMON_ACCESS_BOXED ; 
 int ZFCP_STATUS_COMMON_ACCESS_DENIED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_unit_reopen (struct zfcp_unit*,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static void zfcp_erp_unit_access_changed(struct zfcp_unit *unit, char *id,
					 void *ref)
{
	int status = atomic_read(&unit->status);
	if (!(status & (ZFCP_STATUS_COMMON_ACCESS_DENIED |
			ZFCP_STATUS_COMMON_ACCESS_BOXED)))
		return;

	zfcp_erp_unit_reopen(unit, ZFCP_STATUS_COMMON_ERP_FAILED, id, ref);
}