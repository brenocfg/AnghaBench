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
struct zfcp_unit {int dummy; } ;

/* Variables and functions */
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int ZFCP_STATUS_COMMON_RUNNING ; 
 int /*<<< orphan*/  zfcp_erp_unit_reopen (struct zfcp_unit*,int,char*,void*) ; 

void zfcp_erp_unit_shutdown(struct zfcp_unit *unit, int clear, char *id,
			    void *ref)
{
	int flags = ZFCP_STATUS_COMMON_RUNNING | ZFCP_STATUS_COMMON_ERP_FAILED;
	zfcp_erp_unit_reopen(unit, clear | flags, id, ref);
}