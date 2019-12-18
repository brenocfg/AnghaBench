#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  transport; int /*<<< orphan*/  peer_bda; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  int tGATT_SEC_ACTION ;
struct TYPE_13__ {TYPE_1__* p_tcb; } ;
typedef  TYPE_2__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_BLE_SEC_ACT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_SetEncryption (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GATT_CH_OPEN ; 
#define  GATT_SEC_ENCRYPT 132 
#define  GATT_SEC_ENCRYPT_MITM 131 
#define  GATT_SEC_ENCRYPT_NO_MITM 130 
#define  GATT_SEC_ENC_PENDING 129 
 int GATT_SEC_NONE ; 
#define  GATT_SEC_SIGN_DATA 128 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  gatt_add_pending_enc_channel_clcb (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  gatt_convert_sec_action (int,int /*<<< orphan*/ *) ; 
 int gatt_determine_sec_act (TYPE_2__*) ; 
 int /*<<< orphan*/  gatt_enc_cmpl_cback ; 
 int gatt_get_sec_act (TYPE_1__*) ; 
 int /*<<< orphan*/  gatt_sec_check_complete (scalar_t__,TYPE_2__*,int) ; 
 int /*<<< orphan*/  gatt_set_ch_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_set_sec_act (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gatt_sign_data (TYPE_2__*) ; 

BOOLEAN gatt_security_check_start(tGATT_CLCB *p_clcb)
{
    tGATT_TCB           *p_tcb = p_clcb->p_tcb;
    tGATT_SEC_ACTION    gatt_sec_act;
    tBTM_BLE_SEC_ACT    btm_ble_sec_act;
    BOOLEAN             status = TRUE;
#if (SMP_INCLUDED == TRUE)
    tBTM_STATUS         btm_status;
#endif  ///SMP_INCLUDED == TRUE
    tGATT_SEC_ACTION    sec_act_old =  gatt_get_sec_act(p_tcb);

    gatt_sec_act = gatt_determine_sec_act(p_clcb);

    if (sec_act_old == GATT_SEC_NONE) {
        gatt_set_sec_act(p_tcb, gatt_sec_act);
    }

    switch (gatt_sec_act ) {
    case GATT_SEC_SIGN_DATA:
#if (SMP_INCLUDED == TRUE)
        GATT_TRACE_DEBUG("gatt_security_check_start: Do data signing");
        gatt_sign_data(p_clcb);
#endif  ///SMP_INCLUDED == TRUE
        break;
    case GATT_SEC_ENCRYPT:
    case GATT_SEC_ENCRYPT_NO_MITM:
    case GATT_SEC_ENCRYPT_MITM:
        if (sec_act_old < GATT_SEC_ENCRYPT) {
            GATT_TRACE_DEBUG("gatt_security_check_start: Encrypt now or key upgreade first");
            gatt_convert_sec_action(gatt_sec_act, &btm_ble_sec_act);
#if (SMP_INCLUDED == TRUE)
            btm_status = BTM_SetEncryption(p_tcb->peer_bda, p_tcb->transport , gatt_enc_cmpl_cback, &btm_ble_sec_act);
            if ( (btm_status != BTM_SUCCESS) && (btm_status != BTM_CMD_STARTED)) {
                GATT_TRACE_ERROR("gatt_security_check_start BTM_SetEncryption failed btm_status=%d", btm_status);
                status = FALSE;
            }
#endif  ///SMP_INCLUDED == TRUE
        }
        if (status) {
            gatt_add_pending_enc_channel_clcb (p_tcb, p_clcb);
        }
        break;
    case GATT_SEC_ENC_PENDING:
        gatt_add_pending_enc_channel_clcb (p_tcb, p_clcb);
        /* wait for link encrypotion to finish */
        break;
    default:
        gatt_sec_check_complete(TRUE, p_clcb, gatt_sec_act);
        break;
    }

    if (status == FALSE) {
        gatt_set_sec_act(p_tcb, GATT_SEC_NONE);
        gatt_set_ch_state(p_tcb, GATT_CH_OPEN);
    }

    return status;
}