#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int peer_ext_fea; scalar_t__ link_flush_tout; int /*<<< orphan*/  handle; } ;
typedef  TYPE_4__ tL2C_LCB ;
struct TYPE_11__ {scalar_t__ mode; } ;
struct TYPE_12__ {scalar_t__ flush_to; scalar_t__ fcr_present; TYPE_2__ fcr; int /*<<< orphan*/  qos; int /*<<< orphan*/  qos_present; } ;
struct TYPE_10__ {int max_held_acks; } ;
struct TYPE_14__ {TYPE_4__* p_lcb; TYPE_3__ our_cfg; int /*<<< orphan*/  bypass_fcs; TYPE_1__ fcrb; } ;
typedef  TYPE_5__ tL2C_CCB ;
typedef  int /*<<< orphan*/  tL2CAP_FCR_OPTS ;
struct TYPE_16__ {scalar_t__ mode; int max_transmit; int tx_win_sz; scalar_t__ rtrans_tout; scalar_t__ mon_tout; } ;
struct TYPE_15__ {scalar_t__ fcs; scalar_t__ flush_to; void* flush_to_present; scalar_t__ fcr_present; TYPE_7__ fcr; void* fcs_present; int /*<<< orphan*/  qos; scalar_t__ qos_present; } ;
typedef  TYPE_6__ tL2CAP_CFG_INFO ;
typedef  int UINT16 ;

/* Variables and functions */
 void* FALSE ; 
 int HCI_MAX_AUTO_FLUSH_TOUT ; 
 scalar_t__ L2CAP_CFG_FCS_BYPASS ; 
 int /*<<< orphan*/  L2CAP_CFG_FCS_OUR ; 
 int L2CAP_EXTFEA_NO_CRC ; 
 scalar_t__ L2CAP_FCR_BASIC_MODE ; 
 scalar_t__ L2CAP_FCR_STREAM_MODE ; 
 scalar_t__ L2CAP_NO_AUTOMATIC_FLUSH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btsnd_hcic_write_auto_flush_tout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

void l2cu_process_our_cfg_req (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    tL2C_LCB    *p_lcb;
    UINT16      hci_flush_to;

    /* Save the QOS settings we are using for transmit */
    if (p_cfg->qos_present) {
        p_ccb->our_cfg.qos_present = TRUE;
        p_ccb->our_cfg.qos         = p_cfg->qos;
    }

    if (p_cfg->fcr_present) {
        /* Override FCR options if attempting streaming or basic */
        if (p_cfg->fcr.mode == L2CAP_FCR_BASIC_MODE) {
            memset(&p_cfg->fcr, 0, sizeof(tL2CAP_FCR_OPTS));
        } else {
            /* On BR/EDR, timer values are zero in config request */
            /* On class 2 AMP, timer value in config request shall be non-0 processing time */
            /*                 timer value in config response shall be greater than received processing time */
            p_cfg->fcr.mon_tout = p_cfg->fcr.rtrans_tout = 0;

            if (p_cfg->fcr.mode == L2CAP_FCR_STREAM_MODE) {
                p_cfg->fcr.max_transmit = p_cfg->fcr.tx_win_sz = 0;
            }
        }

        /* Set the threshold to send acks (may be updated in the cfg response) */
        p_ccb->fcrb.max_held_acks = p_cfg->fcr.tx_win_sz / 3;

        /* Include FCS option only if peer can handle it */
        if (p_ccb->p_lcb->peer_ext_fea & L2CAP_EXTFEA_NO_CRC) {
            /* FCS check can be bypassed if peer also desires to bypass */
            if (p_cfg->fcs_present && p_cfg->fcs == L2CAP_CFG_FCS_BYPASS) {
                p_ccb->bypass_fcs |= L2CAP_CFG_FCS_OUR;
            }
        } else {
            p_cfg->fcs_present = FALSE;
        }
    } else {
        p_cfg->fcr.mode = L2CAP_FCR_BASIC_MODE;
    }

    p_ccb->our_cfg.fcr.mode    = p_cfg->fcr.mode;
    p_ccb->our_cfg.fcr_present = p_cfg->fcr_present;

    /* Check the flush timeout. If it is lower than the current one used */
    /* then we need to adjust the flush timeout sent to the controller   */
    if (p_cfg->flush_to_present) {
        if ((p_cfg->flush_to == 0) || (p_cfg->flush_to == L2CAP_NO_AUTOMATIC_FLUSH)) {
            /* don't send invalid flush timeout */
            /* SPEC: The sender of the Request shall specify its flush timeout value */
            /*       if it differs from the default value of 0xFFFF                  */
            p_cfg->flush_to_present = FALSE;
        } else {
            p_ccb->our_cfg.flush_to = p_cfg->flush_to;
            p_lcb = p_ccb->p_lcb;

            if (p_cfg->flush_to < p_lcb->link_flush_tout) {
                p_lcb->link_flush_tout = p_cfg->flush_to;

                /* If the timeout is within range of HCI, set the flush timeout */
                if (p_cfg->flush_to <= ((HCI_MAX_AUTO_FLUSH_TOUT * 5) / 8)) {
                    /* Convert flush timeout to 0.625 ms units, with round */
                    hci_flush_to = ((p_cfg->flush_to * 8) + 3) / 5;
                    btsnd_hcic_write_auto_flush_tout (p_lcb->handle, hci_flush_to);
                }
            }
        }
    }
}