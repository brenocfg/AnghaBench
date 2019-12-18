#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ tBTA_AG_REGISTER ;
struct TYPE_7__ {int /*<<< orphan*/  event; } ;
struct TYPE_9__ {TYPE_1__ hdr; } ;
typedef  TYPE_3__ tBTA_AG_DATA ;
typedef  int /*<<< orphan*/  tBTA_AG ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,unsigned int) ; 
 int /*<<< orphan*/  BTA_AG_FAIL_RESOURCES ; 
 int /*<<< orphan*/  BTA_AG_REGISTER_EVT ; 
 TYPE_5__ bta_ag_cb ; 
 int /*<<< orphan*/ * bta_ag_scb_alloc () ; 
 int /*<<< orphan*/  bta_ag_sm_execute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_ag_api_register(tBTA_AG_DATA *p_data)
{
    tBTA_AG_SCB     *p_scb;
    tBTA_AG_REGISTER reg;

    /* allocate an scb */
    if ((p_scb = bta_ag_scb_alloc()) != NULL) {
        APPL_TRACE_DEBUG("bta_ag_api_register: p_scb 0x%08x ", (unsigned int)p_scb);
        bta_ag_sm_execute(p_scb, p_data->hdr.event, p_data);
    } else {
        reg.status = BTA_AG_FAIL_RESOURCES;
        (*bta_ag_cb.p_cback)(BTA_AG_REGISTER_EVT, (tBTA_AG *) &reg);
    }
}