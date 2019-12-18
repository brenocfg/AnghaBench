#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_5__*) ;} ;
typedef  TYPE_3__ tBTA_GATTC_RCB ;
struct TYPE_10__ {int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  client_if; } ;
struct TYPE_13__ {TYPE_1__ enc_cmpl; } ;
typedef  TYPE_4__ tBTA_GATTC_DATA ;
typedef  int /*<<< orphan*/  tBTA_GATTC_CB ;
struct TYPE_11__ {int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  client_if; } ;
struct TYPE_14__ {TYPE_2__ enc_cmpl; } ;
typedef  TYPE_5__ tBTA_GATTC ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_ENC_CMPL_CB_EVT ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* bta_gattc_cl_get_regcb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_5__*) ; 

void bta_gattc_process_enc_cmpl(tBTA_GATTC_CB *p_cb, tBTA_GATTC_DATA *p_msg)
{
    tBTA_GATTC_RCB *p_clreg;
    tBTA_GATTC cb_data;
    UNUSED(p_cb);

    p_clreg = bta_gattc_cl_get_regcb(p_msg->enc_cmpl.client_if);

    if (p_clreg && p_clreg->p_cback) {
        memset(&cb_data, 0, sizeof(tBTA_GATTC));

        cb_data.enc_cmpl.client_if = p_msg->enc_cmpl.client_if;
        bdcpy(cb_data.enc_cmpl.remote_bda, p_msg->enc_cmpl.remote_bda);

        (*p_clreg->p_cback)(BTA_GATTC_ENC_CMPL_CB_EVT, &cb_data);
    }
}