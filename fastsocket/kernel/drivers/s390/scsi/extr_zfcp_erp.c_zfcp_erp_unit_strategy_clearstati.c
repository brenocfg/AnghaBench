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
 int ZFCP_STATUS_COMMON_ACCESS_DENIED ; 
 int ZFCP_STATUS_UNIT_READONLY ; 
 int ZFCP_STATUS_UNIT_SHARED ; 
 int /*<<< orphan*/  atomic_clear_mask (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfcp_erp_unit_strategy_clearstati(struct zfcp_unit *unit)
{
	atomic_clear_mask(ZFCP_STATUS_COMMON_ACCESS_DENIED |
			  ZFCP_STATUS_UNIT_SHARED |
			  ZFCP_STATUS_UNIT_READONLY,
			  &unit->status);
}