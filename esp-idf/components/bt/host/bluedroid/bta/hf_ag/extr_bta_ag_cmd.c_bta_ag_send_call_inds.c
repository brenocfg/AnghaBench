#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  call_ind; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  size_t tBTA_AG_RES ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_CALL_ACTIVE ; 
 int /*<<< orphan*/  BTA_AG_CALL_INACTIVE ; 
 size_t BTA_AG_END_CALL_RES ; 
 int /*<<< orphan*/  BTA_AG_IND_CALL ; 
 int /*<<< orphan*/  BTA_AG_IND_CALLSETUP ; 
 size_t BTA_AG_IN_CALL_CONN_RES ; 
 size_t BTA_AG_IN_CALL_HELD_RES ; 
 size_t BTA_AG_OUT_CALL_CONN_RES ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * bta_ag_callsetup_ind_tbl ; 
 int /*<<< orphan*/  bta_ag_send_ind (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_ag_send_call_inds(tBTA_AG_SCB *p_scb, tBTA_AG_RES result)
{
    UINT8 call = p_scb->call_ind;
    UINT8 callsetup;
    /* set new call and callsetup values based on BTA_AgResult */
    callsetup = bta_ag_callsetup_ind_tbl[result];

    if (result == BTA_AG_END_CALL_RES) {
        call = BTA_AG_CALL_INACTIVE;
    } else if (result == BTA_AG_IN_CALL_CONN_RES || result == BTA_AG_OUT_CALL_CONN_RES
             || result == BTA_AG_IN_CALL_HELD_RES) {
        call = BTA_AG_CALL_ACTIVE;
    } else {
        call = p_scb->call_ind;
    }
    /* Send indicator function tracks if the values have actually changed */
    bta_ag_send_ind(p_scb, BTA_AG_IND_CALL, call, FALSE);
    bta_ag_send_ind(p_scb, BTA_AG_IND_CALLSETUP, callsetup, FALSE);
}