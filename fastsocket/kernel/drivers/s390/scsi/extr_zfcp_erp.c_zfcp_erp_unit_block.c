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
 int /*<<< orphan*/  ZFCP_CLEAR ; 
 int ZFCP_STATUS_COMMON_UNBLOCKED ; 
 int /*<<< orphan*/  zfcp_erp_modify_unit_status (struct zfcp_unit*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_erp_unit_block(struct zfcp_unit *unit, int clear_mask)
{
	zfcp_erp_modify_unit_status(unit, "erublk1", NULL,
				    ZFCP_STATUS_COMMON_UNBLOCKED | clear_mask,
				    ZFCP_CLEAR);
}