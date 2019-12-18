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
struct zfcp_unit {int /*<<< orphan*/  erp_action; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ZFCP_STATUS_COMMON_ERP_INUSE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_action_dismiss (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfcp_erp_action_dismiss_unit(struct zfcp_unit *unit)
{
	if (atomic_read(&unit->status) & ZFCP_STATUS_COMMON_ERP_INUSE)
		zfcp_erp_action_dismiss(&unit->erp_action);
}