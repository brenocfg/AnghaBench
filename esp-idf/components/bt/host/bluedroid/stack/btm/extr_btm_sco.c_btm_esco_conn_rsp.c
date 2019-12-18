#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ link_type; } ;
struct TYPE_12__ {size_t packet_types; int /*<<< orphan*/  retrans_effort; int /*<<< orphan*/  voice_contfmt; int /*<<< orphan*/  max_latency; int /*<<< orphan*/  rx_bw; int /*<<< orphan*/  tx_bw; } ;
struct TYPE_10__ {TYPE_2__ data; TYPE_5__ setup; } ;
struct TYPE_11__ {scalar_t__ state; TYPE_3__ esco; } ;
typedef  TYPE_4__ tSCO_CONN ;
typedef  TYPE_5__ tBTM_ESCO_PARAMS ;
typedef  scalar_t__ UINT8 ;
typedef  size_t UINT16 ;
struct TYPE_8__ {TYPE_5__ def_esco_parms; int /*<<< orphan*/  esco_supported; TYPE_4__* sco_db; } ;
struct TYPE_13__ {size_t btm_sco_pkt_types_supported; TYPE_1__ sco_cb; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTM_LINK_TYPE_SCO ; 
 size_t BTM_MAX_SCO_LINKS ; 
 size_t BTM_SCO_EXCEPTION_PKTS_MASK ; 
 size_t BTM_SCO_LINK_ONLY_MASK ; 
 size_t BTM_SCO_SUPPORTED_PKTS_MASK ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 scalar_t__ HCI_SUCCESS ; 
 scalar_t__ SCO_ST_CONNECTING ; 
 scalar_t__ SCO_ST_LISTENING ; 
 scalar_t__ SCO_ST_UNUSED ; 
 scalar_t__ SCO_ST_W4_CONN_RSP ; 
 TYPE_7__ btm_cb ; 
 scalar_t__ btsnd_hcic_accept_esco_conn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  btsnd_hcic_reject_conn (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btsnd_hcic_reject_esco_conn (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void btm_esco_conn_rsp (UINT16 sco_inx, UINT8 hci_status, BD_ADDR bda,
                               tBTM_ESCO_PARAMS *p_parms)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN        *p_sco = NULL;
    tBTM_ESCO_PARAMS *p_setup;
    UINT16            temp_pkt_types;

    if (sco_inx < BTM_MAX_SCO_LINKS) {
        p_sco = &btm_cb.sco_cb.sco_db[sco_inx];
    }

    /* Reject the connect request if refused by caller or wrong state */
    if (hci_status != HCI_SUCCESS || p_sco == NULL) {
        if (p_sco) {
            p_sco->state = (p_sco->state == SCO_ST_W4_CONN_RSP) ? SCO_ST_LISTENING
                           : SCO_ST_UNUSED;
        }

        if (!btm_cb.sco_cb.esco_supported) {
            if (!btsnd_hcic_reject_conn (bda, hci_status)) {
                BTM_TRACE_ERROR("Could not reject (e)SCO conn: No Buffer!!!");
            }
        } else {
            if (!btsnd_hcic_reject_esco_conn (bda, hci_status)) {
                BTM_TRACE_ERROR("Could not reject (e)SCO conn: No Buffer!!!");
            }
        }
    } else { /* Connection is being accepted */
        p_sco->state = SCO_ST_CONNECTING;
        p_setup = &p_sco->esco.setup;
        /* If parameters not specified use the default */
        if (p_parms) {
            *p_setup = *p_parms;
        } else { /* Use the last setup passed thru BTM_SetEscoMode (or defaults) */
            *p_setup = btm_cb.sco_cb.def_esco_parms;
        }

        temp_pkt_types = (p_setup->packet_types &
                          BTM_SCO_SUPPORTED_PKTS_MASK &
                          btm_cb.btm_sco_pkt_types_supported);

        /* Make sure at least one eSCO packet type is sent, else might confuse peer */
        /* Taking this out to confirm with BQB tests
        ** Real application would like to include this though, as many devices
        ** do not retry with SCO only if an eSCO connection fails.
        if (!(temp_pkt_types & BTM_ESCO_LINK_ONLY_MASK))
        {
            temp_pkt_types |= BTM_SCO_PKT_TYPES_MASK_EV3;
        }
        */
        /* If SCO request, remove eSCO packet types (conformance) */
        if (p_sco->esco.data.link_type == BTM_LINK_TYPE_SCO) {
            temp_pkt_types &= BTM_SCO_LINK_ONLY_MASK;
            temp_pkt_types |= BTM_SCO_EXCEPTION_PKTS_MASK;
        } else {
            /* OR in any exception packet types */
            temp_pkt_types |= ((p_setup->packet_types & BTM_SCO_EXCEPTION_PKTS_MASK) |
                               (btm_cb.btm_sco_pkt_types_supported & BTM_SCO_EXCEPTION_PKTS_MASK));
        }

        if (btsnd_hcic_accept_esco_conn (bda, p_setup->tx_bw, p_setup->rx_bw,
                                         p_setup->max_latency, p_setup->voice_contfmt,
                                         p_setup->retrans_effort, temp_pkt_types)) {
            p_setup->packet_types = temp_pkt_types;
        } else {
            BTM_TRACE_ERROR("Could not accept SCO conn: No Buffer!!!");
        }
    }
#endif
}