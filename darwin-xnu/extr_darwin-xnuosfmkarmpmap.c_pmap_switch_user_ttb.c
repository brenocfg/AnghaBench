#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmap_t ;
struct TYPE_5__ {int /*<<< orphan*/  asid; int /*<<< orphan*/  vasid; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_TRACE (int,int,...) ; 
 int /*<<< orphan*/  PMAP__SWITCH_USER_TTB ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDE (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_switch_user_ttb_internal (TYPE_1__*) ; 

void
pmap_switch_user_ttb(
	pmap_t pmap)
{
	PMAP_TRACE(1, PMAP_CODE(PMAP__SWITCH_USER_TTB) | DBG_FUNC_START, VM_KERNEL_ADDRHIDE(pmap), pmap->vasid, pmap->asid);
	pmap_switch_user_ttb_internal(pmap);
	PMAP_TRACE(1, PMAP_CODE(PMAP__SWITCH_USER_TTB) | DBG_FUNC_END);
}