#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  status; int /*<<< orphan*/  client_if; } ;
struct TYPE_11__ {TYPE_1__ reg_oper; int /*<<< orphan*/  client_if; int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_2__ tBTA_GATTC_RCB ;
typedef  int /*<<< orphan*/  tBTA_GATTC_IF ;
typedef  int /*<<< orphan*/  (* tBTA_GATTC_CBACK ) (int /*<<< orphan*/ ,TYPE_2__*) ;
struct TYPE_12__ {scalar_t__ state; } ;
typedef  TYPE_4__ tBTA_GATTC_CB ;
typedef  TYPE_2__ tBTA_GATTC ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_DEREG_EVT ; 
 scalar_t__ BTA_GATTC_STATE_DISABLED ; 
 scalar_t__ BTA_GATTC_STATE_DISABLING ; 
 int /*<<< orphan*/  BTA_GATT_OK ; 
 int /*<<< orphan*/  GATT_Deregister (int /*<<< orphan*/ ) ; 
 TYPE_4__ bta_gattc_cb ; 
 scalar_t__ bta_gattc_num_reg_app () ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void bta_gattc_deregister_cmpl(tBTA_GATTC_RCB *p_clreg)
{
    tBTA_GATTC_CB       *p_cb = &bta_gattc_cb;
    tBTA_GATTC_IF       client_if = p_clreg->client_if;
    tBTA_GATTC          cb_data;
    tBTA_GATTC_CBACK    *p_cback = p_clreg->p_cback;

    memset(&cb_data, 0, sizeof(tBTA_GATTC));

    GATT_Deregister(p_clreg->client_if);
    memset(p_clreg, 0, sizeof(tBTA_GATTC_RCB));

    cb_data.reg_oper.client_if = client_if;
    cb_data.reg_oper.status    = BTA_GATT_OK;

    if (p_cback)
        /* callback with de-register event */
    {
        (*p_cback)(BTA_GATTC_DEREG_EVT,  (tBTA_GATTC *)&cb_data);
    }

    if (bta_gattc_num_reg_app() == 0 && p_cb->state == BTA_GATTC_STATE_DISABLING) {
        p_cb->state = BTA_GATTC_STATE_DISABLED;
    }
}