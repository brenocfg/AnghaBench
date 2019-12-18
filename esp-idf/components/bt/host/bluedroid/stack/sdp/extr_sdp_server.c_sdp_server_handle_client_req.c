#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  timer_entry; } ;
typedef  TYPE_1__ tCONN_CB ;
typedef  int UINT8 ;
typedef  int UINT16 ;
struct TYPE_10__ {int offset; int len; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BE_STREAM_TO_UINT16 (int,int*) ; 
 int /*<<< orphan*/  BTU_TTYPE_SDP ; 
 int /*<<< orphan*/  SDP_INACT_TIMEOUT ; 
 int /*<<< orphan*/  SDP_INVALID_PDU_SIZE ; 
 int /*<<< orphan*/  SDP_INVALID_REQ_SYNTAX ; 
#define  SDP_PDU_SERVICE_ATTR_REQ 130 
#define  SDP_PDU_SERVICE_SEARCH_ATTR_REQ 129 
#define  SDP_PDU_SERVICE_SEARCH_REQ 128 
 int /*<<< orphan*/  SDP_TEXT_BAD_HEADER ; 
 int /*<<< orphan*/  SDP_TEXT_BAD_PDU ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*,int) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_service_attr_req (TYPE_1__*,int,int,int*,int*) ; 
 int /*<<< orphan*/  process_service_search (TYPE_1__*,int,int,int*,int*) ; 
 int /*<<< orphan*/  process_service_search_attr_req (TYPE_1__*,int,int,int*,int*) ; 
 int /*<<< orphan*/  sdpu_build_n_send_error (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sdp_server_handle_client_req (tCONN_CB *p_ccb, BT_HDR *p_msg)
{
    UINT8   *p_req     = (UINT8 *) (p_msg + 1) + p_msg->offset;
    UINT8   *p_req_end = p_req + p_msg->len;
    UINT8   pdu_id;
    UINT16  trans_num, param_len;


    /* Start inactivity timer */
    btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_SDP, SDP_INACT_TIMEOUT);

    /* The first byte in the message is the pdu type */
    pdu_id = *p_req++;

    /* Extract the transaction number and parameter length */
    BE_STREAM_TO_UINT16 (trans_num, p_req);
    BE_STREAM_TO_UINT16 (param_len, p_req);

    if ((p_req + param_len) != p_req_end) {
        sdpu_build_n_send_error (p_ccb, trans_num, SDP_INVALID_PDU_SIZE, SDP_TEXT_BAD_HEADER);
        return;
    }

    switch (pdu_id) {
    case SDP_PDU_SERVICE_SEARCH_REQ:
        process_service_search (p_ccb, trans_num, param_len, p_req, p_req_end);
        break;

    case SDP_PDU_SERVICE_ATTR_REQ:
        process_service_attr_req (p_ccb, trans_num, param_len, p_req, p_req_end);
        break;

    case SDP_PDU_SERVICE_SEARCH_ATTR_REQ:
        process_service_search_attr_req (p_ccb, trans_num, param_len, p_req, p_req_end);
        break;

    default:
        sdpu_build_n_send_error (p_ccb, trans_num, SDP_INVALID_REQ_SYNTAX, SDP_TEXT_BAD_PDU);
        SDP_TRACE_WARNING ("SDP - server got unknown PDU: 0x%x\n", pdu_id);
        break;
    }
}