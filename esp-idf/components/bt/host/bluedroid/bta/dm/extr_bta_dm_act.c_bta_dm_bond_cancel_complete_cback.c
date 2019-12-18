#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_5__ {int /*<<< orphan*/  result; } ;
struct TYPE_6__ {TYPE_1__ bond_cancel_cmpl; } ;
typedef  TYPE_2__ tBTA_DM_SEC ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_sec_cback ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_BOND_CANCEL_CMPL_EVT ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 int /*<<< orphan*/  BTA_SUCCESS ; 
 scalar_t__ BTM_SUCCESS ; 
 TYPE_4__ bta_dm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void bta_dm_bond_cancel_complete_cback(tBTM_STATUS result)
{

    tBTA_DM_SEC sec_event;

    if (result == BTM_SUCCESS) {
        sec_event.bond_cancel_cmpl.result = BTA_SUCCESS;
    } else {
        sec_event.bond_cancel_cmpl.result = BTA_FAILURE;
    }

    if (bta_dm_cb.p_sec_cback) {
        bta_dm_cb.p_sec_cback(BTA_DM_BOND_CANCEL_CMPL_EVT, &sec_event);
    }
}