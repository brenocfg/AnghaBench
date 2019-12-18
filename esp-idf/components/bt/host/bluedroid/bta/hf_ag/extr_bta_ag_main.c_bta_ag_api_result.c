#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ svc_conn; scalar_t__ in_use; } ;
typedef  TYPE_2__ tBTA_AG_SCB ;
struct TYPE_9__ {scalar_t__ layer_specific; } ;
struct TYPE_11__ {TYPE_1__ hdr; } ;
typedef  TYPE_3__ tBTA_AG_DATA ;
struct TYPE_12__ {TYPE_2__* scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,unsigned int) ; 
 int /*<<< orphan*/  BTA_AG_API_RESULT_EVT ; 
 scalar_t__ BTA_AG_HANDLE_ALL ; 
 int BTA_AG_NUM_SCB ; 
 TYPE_7__ bta_ag_cb ; 
 TYPE_2__* bta_ag_scb_by_idx (scalar_t__) ; 
 int /*<<< orphan*/  bta_ag_sm_execute (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void bta_ag_api_result(tBTA_AG_DATA *p_data)
{
    tBTA_AG_SCB     *p_scb;
    int i;
    
    if (p_data->hdr.layer_specific != BTA_AG_HANDLE_ALL) {
        if ((p_scb = bta_ag_scb_by_idx(p_data->hdr.layer_specific)) != NULL) {
            APPL_TRACE_DEBUG("bta_ag_api_result: p_scb 0x%08x ", (unsigned int)p_scb);
            bta_ag_sm_execute(p_scb, BTA_AG_API_RESULT_EVT, p_data);
        }
    } else {
        for (i = 0, p_scb = &bta_ag_cb.scb[0]; i < BTA_AG_NUM_SCB; i++, p_scb++) {
            if (p_scb->in_use && p_scb->svc_conn) {
                APPL_TRACE_DEBUG("bta_ag_api_result p_scb 0x%08x ", (unsigned int)p_scb);
                bta_ag_sm_execute(p_scb, BTA_AG_API_RESULT_EVT, p_data);
            }
        }
    }
}