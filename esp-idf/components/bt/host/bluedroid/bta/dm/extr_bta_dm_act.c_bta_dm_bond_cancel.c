#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_9__ {int /*<<< orphan*/  result; } ;
struct TYPE_10__ {TYPE_2__ bond_cancel_cmpl; } ;
typedef  TYPE_3__ tBTA_DM_SEC ;
struct TYPE_8__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_11__ {TYPE_1__ bond_cancel; } ;
typedef  TYPE_4__ tBTA_DM_MSG ;
struct TYPE_12__ {int /*<<< orphan*/  (* p_sec_cback ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  BTA_DM_BOND_CANCEL_CMPL_EVT ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 scalar_t__ BTM_CMD_STARTED ; 
 scalar_t__ BTM_SUCCESS ; 
 scalar_t__ BTM_SecBondCancel (int /*<<< orphan*/ ) ; 
 TYPE_6__ bta_dm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

void bta_dm_bond_cancel (tBTA_DM_MSG *p_data)
{
    tBTM_STATUS status;
    tBTA_DM_SEC sec_event;

    APPL_TRACE_EVENT(" bta_dm_bond_cancel ");
    status = BTM_SecBondCancel ( p_data->bond_cancel.bd_addr );

    if (bta_dm_cb.p_sec_cback && (status != BTM_CMD_STARTED && status != BTM_SUCCESS)) {
        sec_event.bond_cancel_cmpl.result = BTA_FAILURE;

        bta_dm_cb.p_sec_cback(BTA_DM_BOND_CANCEL_CMPL_EVT, &sec_event);
    }

}