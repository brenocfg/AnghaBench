#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ in_use; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
struct TYPE_5__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__* scb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTA_AG_API_DEREGISTER_EVT ; 
 int /*<<< orphan*/  BTA_AG_DISABLE_EVT ; 
 int BTA_AG_NUM_SCB ; 
 int /*<<< orphan*/  BTA_ID_AG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ bta_ag_cb ; 
 int /*<<< orphan*/  bta_ag_sm_execute (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_sys_collision_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_sys_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_is_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_ag_api_disable(tBTA_AG_DATA *p_data)
{
    /* deregister all scbs in use */
    tBTA_AG_SCB     *p_scb = &bta_ag_cb.scb[0];
    BOOLEAN         do_dereg = FALSE;
    int             i;

    if (!bta_sys_is_register (BTA_ID_AG)) {
        APPL_TRACE_ERROR("BTA AG is already disabled, ignoring ...");
        return;
    }
    /* De-register with BTA system manager */
    bta_sys_deregister(BTA_ID_AG);

    for (i = 0; i < BTA_AG_NUM_SCB; i++, p_scb++) {
        if (p_scb->in_use) {
            bta_ag_sm_execute(p_scb, BTA_AG_API_DEREGISTER_EVT, p_data);
            do_dereg = TRUE;
        }
    }

    if (!do_dereg) {
        /* Done, send callback evt to app */
        (*bta_ag_cb.p_cback)(BTA_AG_DISABLE_EVT, NULL);
    }
    bta_sys_collision_register (BTA_ID_AG, NULL);
}