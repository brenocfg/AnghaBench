#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int features; size_t inband_enabled; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  app_id; int /*<<< orphan*/  act_timer; int /*<<< orphan*/  post_sco; int /*<<< orphan*/  hsp_version; } ;
typedef  TYPE_2__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
struct TYPE_16__ {size_t state; int /*<<< orphan*/  ok_flag; int /*<<< orphan*/ * str; int /*<<< orphan*/  audio_handle; int /*<<< orphan*/  num; } ;
struct TYPE_18__ {size_t result; TYPE_1__ data; } ;
typedef  TYPE_3__ tBTA_AG_API_RESULT ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,size_t) ; 
#define  BTA_AG_END_CALL_RES 135 
 int /*<<< orphan*/  BTA_AG_ERR_INV_CHAR_IN_TSTR ; 
 int BTA_AG_FEAT_NOSCO ; 
 int /*<<< orphan*/  BTA_AG_HANDLE_NONE ; 
#define  BTA_AG_INBAND_RING_RES 134 
#define  BTA_AG_IN_CALL_CONN_RES 133 
#define  BTA_AG_IN_CALL_RES 132 
#define  BTA_AG_MIC_RES 131 
 int /*<<< orphan*/  BTA_AG_OK_DONE ; 
 int /*<<< orphan*/  BTA_AG_OK_ERROR ; 
#define  BTA_AG_OUT_CALL_ORIG_RES 130 
 int /*<<< orphan*/  BTA_AG_POST_SCO_NONE ; 
 int /*<<< orphan*/  BTA_AG_POST_SCO_RING ; 
#define  BTA_AG_SPK_RES 129 
#define  BTA_AG_UNAT_RES 128 
 int /*<<< orphan*/  BTA_ID_AG ; 
 int /*<<< orphan*/  HSP_VERSION_1_2 ; 
 int /*<<< orphan*/  bta_ag_inband_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_ag_sco_close (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_ag_sco_is_open (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_ag_sco_is_opening (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_ag_sco_open (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_ag_send_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_send_ok (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_ag_send_result (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_send_ring (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bta_ag_trans_result ; 
 int /*<<< orphan*/  bta_sys_sco_unuse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sco_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_stop_timer (int /*<<< orphan*/ *) ; 

void bta_ag_hsp_result(tBTA_AG_SCB *p_scb, tBTA_AG_API_RESULT *p_result)
{
    UINT8 code = bta_ag_trans_result[p_result->result];

    APPL_TRACE_DEBUG("bta_ag_hsp_result : res = %d", p_result->result);

    switch(p_result->result) {
        case BTA_AG_SPK_RES:
        case BTA_AG_MIC_RES:
            bta_ag_send_result(p_scb, code, NULL, p_result->data.num);
            break;

        case BTA_AG_IN_CALL_RES:
        {
            /* tell sys to stop av if any */
            bta_sys_sco_use(BTA_ID_AG, p_scb->app_id, p_scb->peer_addr);
            /* if sco already opened or no inband ring send ring now */
            if (bta_ag_sco_is_open(p_scb) || !bta_ag_inband_enabled(p_scb) ||
                (p_scb->features & BTA_AG_FEAT_NOSCO)) {
                bta_ag_send_ring(p_scb, (tBTA_AG_DATA *) p_result);
            } else {
                /* else open sco, send ring after sco opened */
                /* HSPv1.2: AG shall not send RING if using in-band ring tone. */
                if (p_scb->hsp_version >= HSP_VERSION_1_2) {
                    p_scb->post_sco = BTA_AG_POST_SCO_NONE;
                } else {
                    p_scb->post_sco = BTA_AG_POST_SCO_RING;
                }
                bta_ag_sco_open(p_scb, (tBTA_AG_DATA *) p_result);
            }
            break;
        }

        case BTA_AG_IN_CALL_CONN_RES:
        case BTA_AG_OUT_CALL_ORIG_RES:
        {
            /* if incoming call connected stop ring timer */
            if (p_result->result == BTA_AG_IN_CALL_CONN_RES) {
                bta_sys_stop_timer(&p_scb->act_timer);
            }

            if (!(p_scb->features & BTA_AG_FEAT_NOSCO)) {
                /* if audio connected to this scb open sco */
                if (p_result->data.audio_handle == bta_ag_scb_to_idx(p_scb)) {
                    bta_ag_sco_open(p_scb, (tBTA_AG_DATA *) p_result);
                } else if (p_result->data.audio_handle == BTA_AG_HANDLE_NONE) {
                    /* else if no audio at call close sco */
                    bta_ag_sco_close(p_scb, (tBTA_AG_DATA *) p_result);
                }
            }
            break;
        }

        case BTA_AG_END_CALL_RES:
        {
            /* stop ring timer */
            bta_sys_stop_timer(&p_scb->act_timer);
            /* close sco */
            if ((bta_ag_sco_is_open(p_scb) || bta_ag_sco_is_opening(p_scb)) && !(p_scb->features & BTA_AG_FEAT_NOSCO)) {
                bta_ag_sco_close(p_scb, (tBTA_AG_DATA *) p_result);
            } else {
                /* if av got suspended by this call, let it resume. */
                bta_sys_sco_unuse(BTA_ID_AG, p_scb->app_id, p_scb->peer_addr);
            }
            break;
        }

        case BTA_AG_INBAND_RING_RES:
            p_scb->inband_enabled = p_result->data.state;
            APPL_TRACE_DEBUG("inband_enabled set to %d", p_scb->inband_enabled);
            break;

        case BTA_AG_UNAT_RES:
        {
            if (p_result->data.ok_flag != BTA_AG_OK_ERROR) {
                if (p_result->data.str[0] != 0) {
                    bta_ag_send_result(p_scb, code, p_result->data.str, 0);
                }
                if (p_result->data.ok_flag == BTA_AG_OK_DONE) {
                    bta_ag_send_ok(p_scb);
                }
            } else {
                bta_ag_send_error(p_scb, BTA_AG_ERR_INV_CHAR_IN_TSTR);
            }
            break;
        }
        default:
            break; /* ignore all others */
    }
}