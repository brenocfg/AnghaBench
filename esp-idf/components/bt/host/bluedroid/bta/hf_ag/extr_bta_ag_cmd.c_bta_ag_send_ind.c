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
struct TYPE_4__ {int bia_masked_out; int call_ind; int callsetup_ind; int service_ind; int signal_ind; int roam_ind; int battchg_ind; int callheld_ind; scalar_t__ cmer_enabled; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  void* UINT8 ;
typedef  int UINT32 ;
typedef  int UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int BTA_AG_IND_BATTCHG ; 
 int BTA_AG_IND_CALL ; 
 int BTA_AG_IND_CALLHELD ; 
 int BTA_AG_IND_CALLSETUP ; 
 int BTA_AG_IND_ROAM ; 
 int BTA_AG_IND_SERVICE ; 
 int BTA_AG_IND_SIGNAL ; 
 int /*<<< orphan*/  BTA_AG_RES_CIEV ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  bta_ag_send_result (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utl_itoa (int,char*) ; 

__attribute__((used)) static void bta_ag_send_ind(tBTA_AG_SCB *p_scb, UINT16 id, UINT16 value, BOOLEAN on_demand)
{
    char    str[12];
    char    *p = str;
    /* If the indicator is masked out, just return */
    /* Mandatory indicators can not be masked out. */
    if ((p_scb->bia_masked_out & ((UINT32)1 << id)) &&
        ((id != BTA_AG_IND_CALL) && (id != BTA_AG_IND_CALLSETUP) && (id != BTA_AG_IND_CALLHELD)))
        return;

    /* Ensure we do not send duplicate indicators if not requested by app */
    /* If it was requested by app, transmit CIEV even if it is duplicate. */
    if (id == BTA_AG_IND_CALL) {
        if ((value == p_scb->call_ind) && (on_demand == FALSE)) {
            return;
        }
        p_scb->call_ind = (UINT8)value;
    }
    if ((id == BTA_AG_IND_CALLSETUP) && (on_demand == FALSE)) {
        if (value == p_scb->callsetup_ind) {
            return;
        }
        p_scb->callsetup_ind = (UINT8)value;
    }
    if ((id == BTA_AG_IND_SERVICE) && (on_demand == FALSE)) {
        if (value == p_scb->service_ind) {
            return;
        }
        p_scb->service_ind = (UINT8)value;
    }
    if ((id == BTA_AG_IND_SIGNAL) && (on_demand == FALSE)) {
        if (value == p_scb->signal_ind) {
            return;
        }
        p_scb->signal_ind = (UINT8)value;
    }
    if ((id == BTA_AG_IND_ROAM) && (on_demand == FALSE)) {
        if (value == p_scb->roam_ind) {
            return;            
        }
        p_scb->roam_ind = (UINT8)value;
    }
    if ((id == BTA_AG_IND_BATTCHG) && (on_demand == FALSE)) {
        if (value == p_scb->battchg_ind) {
            return;
        }
        p_scb->battchg_ind = (UINT8)value;
    }
    if ((id == BTA_AG_IND_CALLHELD) && (on_demand == FALSE)) {
        /* call swap could result in sending callheld=1 multiple times */
        if ((value != 1) && (value == p_scb->callheld_ind)) {
            return;
        }
        p_scb->callheld_ind = (UINT8)value;
    }
    if (p_scb->cmer_enabled) {
        p += utl_itoa(id, p);
        *p++ = ',';
        utl_itoa(value, p);
        bta_ag_send_result(p_scb, BTA_AG_RES_CIEV, str, 0);
    }
}