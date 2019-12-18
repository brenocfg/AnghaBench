#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_8__* p_lcb; int /*<<< orphan*/  remote_cid; scalar_t__ local_id; } ;
typedef  TYPE_4__ tL2C_CCB ;
struct TYPE_13__ {int /*<<< orphan*/  flush_timeout; int /*<<< orphan*/  access_latency; int /*<<< orphan*/  sdu_inter_time; int /*<<< orphan*/  max_sdu_size; scalar_t__ stype; scalar_t__ id; } ;
struct TYPE_12__ {int /*<<< orphan*/  mps; int /*<<< orphan*/  mon_tout; int /*<<< orphan*/  rtrans_tout; scalar_t__ max_transmit; scalar_t__ tx_win_sz; scalar_t__ mode; } ;
struct TYPE_11__ {int /*<<< orphan*/  delay_variation; int /*<<< orphan*/  latency; int /*<<< orphan*/  peak_bandwidth; int /*<<< orphan*/  token_bucket_size; int /*<<< orphan*/  token_rate; scalar_t__ service_type; scalar_t__ qos_flags; } ;
struct TYPE_15__ {TYPE_3__ ext_flow_spec; scalar_t__ ext_flow_spec_present; scalar_t__ fcs; scalar_t__ fcs_present; TYPE_2__ fcr; scalar_t__ fcr_present; TYPE_1__ qos; scalar_t__ qos_present; int /*<<< orphan*/  flush_to; scalar_t__ flush_to_present; int /*<<< orphan*/  mtu; scalar_t__ mtu_present; int /*<<< orphan*/  flags; } ;
typedef  TYPE_5__ tL2CAP_CFG_INFO ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_16__ {scalar_t__ id; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int HCI_DATA_PREAMBLE_SIZE ; 
 int /*<<< orphan*/  L2CAP_ADJ_ID ; 
 scalar_t__ L2CAP_CFG_EXT_FLOW_OPTION_LEN ; 
 scalar_t__ L2CAP_CFG_FCR_OPTION_LEN ; 
 scalar_t__ L2CAP_CFG_FCS_OPTION_LEN ; 
 scalar_t__ L2CAP_CFG_FLUSH_OPTION_LEN ; 
 scalar_t__ L2CAP_CFG_MTU_OPTION_LEN ; 
 scalar_t__ L2CAP_CFG_OPTION_OVERHEAD ; 
 scalar_t__ L2CAP_CFG_QOS_OPTION_LEN ; 
 scalar_t__ L2CAP_CFG_TYPE_EXT_FLOW ; 
 scalar_t__ L2CAP_CFG_TYPE_FCR ; 
 scalar_t__ L2CAP_CFG_TYPE_FCS ; 
 scalar_t__ L2CAP_CFG_TYPE_FLUSH_TOUT ; 
 scalar_t__ L2CAP_CFG_TYPE_MTU ; 
 scalar_t__ L2CAP_CFG_TYPE_QOS ; 
 int /*<<< orphan*/  L2CAP_CMD_CONFIG_REQ ; 
 int L2CAP_CMD_OVERHEAD ; 
 scalar_t__ L2CAP_CONFIG_REQ_LEN ; 
 int L2CAP_PKT_OVERHEAD ; 
 int L2CAP_SEND_CMD_OFFSET ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cu_adj_id (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * l2cu_build_header (TYPE_8__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void l2cu_send_peer_config_req (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    BT_HDR  *p_buf;
    UINT16  cfg_len = 0;
    UINT8   *p;

    /* Create an identifier for this packet */
    p_ccb->p_lcb->id++;
    l2cu_adj_id(p_ccb->p_lcb, L2CAP_ADJ_ID);

    p_ccb->local_id = p_ccb->p_lcb->id;

    if (p_cfg->mtu_present) {
        cfg_len += L2CAP_CFG_MTU_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    }
    if (p_cfg->flush_to_present) {
        cfg_len += L2CAP_CFG_FLUSH_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    }
    if (p_cfg->qos_present) {
        cfg_len += L2CAP_CFG_QOS_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    }
    if (p_cfg->fcr_present) {
        cfg_len += L2CAP_CFG_FCR_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    }
    if (p_cfg->fcs_present) {
        cfg_len += L2CAP_CFG_FCS_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    }
    if (p_cfg->ext_flow_spec_present) {
        cfg_len += L2CAP_CFG_EXT_FLOW_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    }

    if ((p_buf = l2cu_build_header (p_ccb->p_lcb, (UINT16) (L2CAP_CONFIG_REQ_LEN + cfg_len),
                                    L2CAP_CMD_CONFIG_REQ, p_ccb->local_id)) == NULL ) {
        L2CAP_TRACE_WARNING ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
        L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, p_ccb->remote_cid);
    UINT16_TO_STREAM (p, p_cfg->flags);                    /* Flags (continuation) */

    /* Now, put the options */
    if (p_cfg->mtu_present) {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_MTU);
        UINT8_TO_STREAM  (p, L2CAP_CFG_MTU_OPTION_LEN);
        UINT16_TO_STREAM (p, p_cfg->mtu);
    }
    if (p_cfg->flush_to_present) {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_FLUSH_TOUT);
        UINT8_TO_STREAM  (p, L2CAP_CFG_FLUSH_OPTION_LEN);
        UINT16_TO_STREAM (p, p_cfg->flush_to);
    }
    if (p_cfg->qos_present) {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_QOS);
        UINT8_TO_STREAM  (p, L2CAP_CFG_QOS_OPTION_LEN);
        UINT8_TO_STREAM  (p, p_cfg->qos.qos_flags);
        UINT8_TO_STREAM  (p, p_cfg->qos.service_type);
        UINT32_TO_STREAM (p, p_cfg->qos.token_rate);
        UINT32_TO_STREAM (p, p_cfg->qos.token_bucket_size);
        UINT32_TO_STREAM (p, p_cfg->qos.peak_bandwidth);
        UINT32_TO_STREAM (p, p_cfg->qos.latency);
        UINT32_TO_STREAM (p, p_cfg->qos.delay_variation);
    }
    if (p_cfg->fcr_present) {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_FCR);
        UINT8_TO_STREAM  (p, L2CAP_CFG_FCR_OPTION_LEN);
        UINT8_TO_STREAM  (p, p_cfg->fcr.mode);
        UINT8_TO_STREAM  (p, p_cfg->fcr.tx_win_sz);
        UINT8_TO_STREAM  (p, p_cfg->fcr.max_transmit);
        UINT16_TO_STREAM (p, p_cfg->fcr.rtrans_tout);
        UINT16_TO_STREAM (p, p_cfg->fcr.mon_tout);
        UINT16_TO_STREAM (p, p_cfg->fcr.mps);
    }

    if (p_cfg->fcs_present) {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_FCS);
        UINT8_TO_STREAM  (p, L2CAP_CFG_FCS_OPTION_LEN);
        UINT8_TO_STREAM  (p, p_cfg->fcs);
    }

    if (p_cfg->ext_flow_spec_present) {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_EXT_FLOW);
        UINT8_TO_STREAM  (p, L2CAP_CFG_EXT_FLOW_OPTION_LEN);
        UINT8_TO_STREAM  (p, p_cfg->ext_flow_spec.id);
        UINT8_TO_STREAM  (p, p_cfg->ext_flow_spec.stype);
        UINT16_TO_STREAM (p, p_cfg->ext_flow_spec.max_sdu_size);
        UINT32_TO_STREAM (p, p_cfg->ext_flow_spec.sdu_inter_time);
        UINT32_TO_STREAM (p, p_cfg->ext_flow_spec.access_latency);
        UINT32_TO_STREAM (p, p_cfg->ext_flow_spec.flush_timeout);
    }

    l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, p_buf);
}