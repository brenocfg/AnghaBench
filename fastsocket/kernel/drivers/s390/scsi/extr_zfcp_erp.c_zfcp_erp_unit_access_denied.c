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
 int /*<<< orphan*/  ZFCP_SET ; 
 int ZFCP_STATUS_COMMON_ACCESS_DENIED ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  zfcp_erp_modify_unit_status (struct zfcp_unit*,char*,void*,int,int /*<<< orphan*/ ) ; 

void zfcp_erp_unit_access_denied(struct zfcp_unit *unit, char *id, void *ref)
{
	zfcp_erp_modify_unit_status(unit, id, ref,
				    ZFCP_STATUS_COMMON_ERP_FAILED |
				    ZFCP_STATUS_COMMON_ACCESS_DENIED, ZFCP_SET);
}