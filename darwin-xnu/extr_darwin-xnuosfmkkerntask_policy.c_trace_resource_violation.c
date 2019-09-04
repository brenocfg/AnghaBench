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
struct ledger_entry_info {int /*<<< orphan*/  lei_refill_period; int /*<<< orphan*/  lei_limit; int /*<<< orphan*/  lei_last_refill; int /*<<< orphan*/  lei_balance; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH ; 
 int /*<<< orphan*/  DBG_MACH_RESOURCE ; 
 int /*<<< orphan*/  KDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERNEL_DBG_IST_SANE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
trace_resource_violation(uint16_t code,
                         struct ledger_entry_info *linfo)
{
	KERNEL_DBG_IST_SANE(KDBG_CODE(DBG_MACH, DBG_MACH_RESOURCE, code),
	                    linfo->lei_balance, linfo->lei_last_refill,
	                    linfo->lei_limit, linfo->lei_refill_period);
}