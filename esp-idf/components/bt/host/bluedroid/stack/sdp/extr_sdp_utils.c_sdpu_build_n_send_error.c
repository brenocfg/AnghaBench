#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  connection_id; } ;
typedef  TYPE_1__ tCONN_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_6__ {int offset; int len; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_BE_STREAM (int /*<<< orphan*/ *,char*,int) ; 
 int L2CAP_MIN_OFFSET ; 
 int /*<<< orphan*/  L2CA_DataWrite (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SDP_DATA_BUF_SIZE ; 
 int /*<<< orphan*/  SDP_PDU_ERROR_RESPONSE ; 
 int /*<<< orphan*/  SDP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT16_TO_BE_STREAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UINT8_TO_BE_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

void sdpu_build_n_send_error (tCONN_CB *p_ccb, UINT16 trans_num, UINT16 error_code, char *p_error_text)
{
    UINT8           *p_rsp, *p_rsp_start, *p_rsp_param_len;
    UINT16          rsp_param_len;
    BT_HDR          *p_buf;


    SDP_TRACE_WARNING ("SDP - sdpu_build_n_send_error  code: 0x%x  CID: 0x%x\n",
                       error_code, p_ccb->connection_id);

    /* Get a buffer to use to build and send the packet to L2CAP */
    if ((p_buf = (BT_HDR *)osi_malloc(SDP_DATA_BUF_SIZE)) == NULL) {
        SDP_TRACE_ERROR ("SDP - no buf for err msg\n");
        return;
    }
    p_buf->offset = L2CAP_MIN_OFFSET;
    p_rsp = p_rsp_start = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

    UINT8_TO_BE_STREAM  (p_rsp, SDP_PDU_ERROR_RESPONSE);
    UINT16_TO_BE_STREAM  (p_rsp, trans_num);

    /* Skip the parameter length, we need to add it at the end */
    p_rsp_param_len = p_rsp;
    p_rsp += 2;

    UINT16_TO_BE_STREAM  (p_rsp, error_code);

    /* Unplugfest example traces do not have any error text */
    if (p_error_text) {
        ARRAY_TO_BE_STREAM (p_rsp, p_error_text, (int) strlen (p_error_text));
    }

    /* Go back and put the parameter length into the buffer */
    rsp_param_len = p_rsp - p_rsp_param_len - 2;
    UINT16_TO_BE_STREAM (p_rsp_param_len, rsp_param_len);

    /* Set the length of the SDP data in the buffer */
    p_buf->len = p_rsp - p_rsp_start;


    /* Send the buffer through L2CAP */
    L2CA_DataWrite (p_ccb->connection_id, p_buf);
}