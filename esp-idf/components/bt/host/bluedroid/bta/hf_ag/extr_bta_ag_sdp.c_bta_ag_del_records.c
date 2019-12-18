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
typedef  int tBTA_SERVICE_MASK ;
struct TYPE_6__ {scalar_t__ dealloc; int reg_services; scalar_t__ in_use; } ;
typedef  TYPE_2__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
struct TYPE_7__ {TYPE_1__* profile; TYPE_2__* scb; } ;
struct TYPE_5__ {scalar_t__ sdp_handle; int /*<<< orphan*/  scn; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int) ; 
 int BTA_AG_NUM_IDX ; 
 int BTA_HSP_SERVICE_ID ; 
 int /*<<< orphan*/  BTM_FreeSCN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_SecClrService (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SDP_DeleteRecord (scalar_t__) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_4__ bta_ag_cb ; 
 int /*<<< orphan*/ * bta_ag_sec_id ; 
 int /*<<< orphan*/ * bta_ag_uuid ; 
 int /*<<< orphan*/  bta_sys_remove_uuid (int /*<<< orphan*/ ) ; 

void bta_ag_del_records(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    tBTA_AG_SCB         *p = &bta_ag_cb.scb[0];
    tBTA_SERVICE_MASK   services;
    tBTA_SERVICE_MASK   others = 0;
    int                 i;
    UNUSED(p_data);

    /* get services of all other registered servers */
    for (i = 0; i < BTA_AG_NUM_IDX; i++, p++) {
        if (p_scb == p) {
            continue;
        }
        if (p->in_use && p->dealloc == FALSE) {
            others |= p->reg_services;
        }
    }
    others >>= BTA_HSP_SERVICE_ID;
    services = p_scb->reg_services >> BTA_HSP_SERVICE_ID;
    for (i = 0; i < BTA_AG_NUM_IDX && services != 0; i++, services >>= 1, others >>= 1)
    {
        /* if service registered for this scb and not registered for any other scb */
        if (((services & 1) == 1) && ((others & 1) == 0)) {
            APPL_TRACE_DEBUG("bta_ag_del_records %d", i);
            if (bta_ag_cb.profile[i].sdp_handle != 0) {
                SDP_DeleteRecord(bta_ag_cb.profile[i].sdp_handle);
                bta_ag_cb.profile[i].sdp_handle = 0;
            }
            BTM_FreeSCN(bta_ag_cb.profile[i].scn);
            BTM_SecClrService(bta_ag_sec_id[i]);
            bta_sys_remove_uuid(bta_ag_uuid[i]);
        }
    }
}