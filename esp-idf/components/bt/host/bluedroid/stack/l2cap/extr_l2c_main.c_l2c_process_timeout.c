#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  conn_update_mask; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int /*<<< orphan*/  tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_8__ {int event; scalar_t__ param; } ;
typedef  TYPE_2__ TIMER_LIST_ENT ;

/* Variables and functions */
#define  BTU_TTYPE_L2CAP_CHNL 133 
#define  BTU_TTYPE_L2CAP_FCR_ACK 132 
#define  BTU_TTYPE_L2CAP_HOLD 131 
#define  BTU_TTYPE_L2CAP_INFO 130 
#define  BTU_TTYPE_L2CAP_LINK 129 
#define  BTU_TTYPE_L2CAP_UPDA_CONN_PARAMS 128 
 int /*<<< orphan*/  HCI_ERR_HOST_TIMEOUT ; 
 int /*<<< orphan*/  L2CEVT_ACK_TIMEOUT ; 
 int /*<<< orphan*/  L2CEVT_TIMEOUT ; 
 int /*<<< orphan*/  L2C_BLE_UPDATE_PARAM_FULL ; 
 int /*<<< orphan*/  L2C_BLE_UPDATE_PENDING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  l2c_csm_execute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2c_info_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  l2c_link_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  l2c_process_held_packets (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_send_update_conn_params_cb (TYPE_1__*,int /*<<< orphan*/ ) ; 

void l2c_process_timeout (TIMER_LIST_ENT *p_tle)
{
    /* What type of timeout ? */
    switch (p_tle->event) {
    case BTU_TTYPE_L2CAP_LINK:
        l2c_link_timeout ((tL2C_LCB *)p_tle->param);
        break;
#if (CLASSIC_BT_INCLUDED == TRUE)
    case BTU_TTYPE_L2CAP_CHNL:
        l2c_csm_execute (((tL2C_CCB *)p_tle->param), L2CEVT_TIMEOUT, NULL);
        break;

    case BTU_TTYPE_L2CAP_FCR_ACK:
        l2c_csm_execute (((tL2C_CCB *)p_tle->param), L2CEVT_ACK_TIMEOUT, NULL);
        break;
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    case BTU_TTYPE_L2CAP_HOLD:
        /* Update the timeouts in the hold queue */
        l2c_process_held_packets(TRUE);
        break;

    case BTU_TTYPE_L2CAP_INFO:
        l2c_info_timeout((tL2C_LCB *)p_tle->param);
        break;
    case BTU_TTYPE_L2CAP_UPDA_CONN_PARAMS: {
#if (BLE_INCLUDED == TRUE)
        UINT8 status = HCI_ERR_HOST_TIMEOUT;
        tL2C_LCB *p_lcb = (tL2C_LCB *)p_tle->param;
        if (p_lcb){
            p_lcb->conn_update_mask &= ~L2C_BLE_UPDATE_PENDING;
            p_lcb->conn_update_mask &= ~L2C_BLE_UPDATE_PARAM_FULL;
        }
        l2c_send_update_conn_params_cb(p_lcb, status);
#endif  ///BLE_INCLUDED == TRUE
        break;
    }
    }
}