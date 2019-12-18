#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ result; } ;
typedef  TYPE_1__ tL2CAP_CFG_INFO ;
struct TYPE_9__ {int ch_flags; int /*<<< orphan*/  peer_bda; } ;
typedef  TYPE_2__ tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATTS_SRV_CHG ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 scalar_t__ GATT_CH_CFG ; 
 int /*<<< orphan*/  GATT_CH_OPEN ; 
 int GATT_L2C_CFG_CFM_DONE ; 
 int GATT_L2C_CFG_IND_DONE ; 
 scalar_t__ L2CAP_CFG_OK ; 
 int /*<<< orphan*/  L2CA_DisconnectReq (int /*<<< orphan*/ ) ; 
 scalar_t__ btm_sec_is_a_bonded_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_add_a_bonded_dev_for_srv_chg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_chk_srv_chg (int /*<<< orphan*/ *) ; 
 TYPE_2__* gatt_find_tcb_by_cid (int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_get_ch_state (TYPE_2__*) ; 
 int /*<<< orphan*/ * gatt_is_bda_in_the_srv_chg_clt_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_send_conn_cback (TYPE_2__*) ; 
 int /*<<< orphan*/  gatt_set_ch_state (TYPE_2__*,int /*<<< orphan*/ ) ; 

void gatt_l2cif_config_cfm_cback(UINT16 lcid, tL2CAP_CFG_INFO *p_cfg)
{
    tGATT_TCB       *p_tcb;
    tGATTS_SRV_CHG  *p_srv_chg_clt = NULL;

    /* look up clcb for this channel */
    if ((p_tcb = gatt_find_tcb_by_cid(lcid)) != NULL) {
        /* if in correct state */
        if ( gatt_get_ch_state(p_tcb) == GATT_CH_CFG) {
            /* if result successful */
            if (p_cfg->result == L2CAP_CFG_OK) {
                /* update flags */
                p_tcb->ch_flags |= GATT_L2C_CFG_CFM_DONE;

                /* if configuration complete */
                if (p_tcb->ch_flags & GATT_L2C_CFG_IND_DONE) {
                    gatt_set_ch_state(p_tcb, GATT_CH_OPEN);

                    if ((p_srv_chg_clt = gatt_is_bda_in_the_srv_chg_clt_list(p_tcb->peer_bda)) != NULL) {
#if (GATTS_INCLUDED == TRUE)
                        gatt_chk_srv_chg(p_srv_chg_clt);
#endif  ///GATTS_INCLUDED == TRUE
                    } else {
                        if (btm_sec_is_a_bonded_dev(p_tcb->peer_bda)) {
                            gatt_add_a_bonded_dev_for_srv_chg(p_tcb->peer_bda);
                        }
                    }

                    /* send callback */
                    gatt_send_conn_cback(p_tcb);
                }
            }
            /* else failure */
            else {
                /* Send L2CAP disconnect req */
                L2CA_DisconnectReq(lcid);
            }
        }
    }
}