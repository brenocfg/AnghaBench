#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t list_len; int* rsp_list; scalar_t__ cur_handle; scalar_t__ num_handles; scalar_t__ transaction_id; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  connection_id; TYPE_1__* p_db; int /*<<< orphan*/ * handles; } ;
typedef  TYPE_2__ tCONN_CB ;
typedef  int UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_13__ {scalar_t__ max_attr_list_size; } ;
struct TYPE_12__ {int offset; scalar_t__ len; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_attr_filters; int /*<<< orphan*/ * attr_filters; } ;
typedef  TYPE_3__ BT_HDR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BE_STREAM_TO_UINT16 (scalar_t__,int*) ; 
 int /*<<< orphan*/  BTU_TTYPE_SDP ; 
 scalar_t__ FALSE ; 
 int L2CAP_MIN_OFFSET ; 
 int /*<<< orphan*/  L2CA_DataWrite (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ SDP_DATA_BUF_SIZE ; 
 int /*<<< orphan*/  SDP_DB_FULL ; 
 int /*<<< orphan*/  SDP_INACT_TIMEOUT ; 
 int /*<<< orphan*/  SDP_INVALID_CONT_STATE ; 
 int /*<<< orphan*/  SDP_INVALID_PDU_SIZE ; 
 int SDP_MAX_CONTINUATION_LEN ; 
 scalar_t__ SDP_MAX_LIST_BYTE_COUNT ; 
 int /*<<< orphan*/  SDP_NO_RESOURCES ; 
 int /*<<< orphan*/  SDP_PDU_SERVICE_ATTR_REQ ; 
 int /*<<< orphan*/  SDP_RAW_DATA_INCLUDED ; 
 int /*<<< orphan*/  SDP_SUCCESS ; 
 int /*<<< orphan*/  SDP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UINT16_TO_BE_STREAM (int*,scalar_t__) ; 
 int /*<<< orphan*/  UINT32_TO_BE_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_BE_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ osi_malloc (scalar_t__) ; 
 int /*<<< orphan*/  save_attr_seq (TYPE_2__*,int*,int*) ; 
 TYPE_6__ sdp_cb ; 
 int /*<<< orphan*/  sdp_copy_raw_data (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  sdp_disconnect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int* sdpu_build_attrib_seq (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_service_attr_rsp (tCONN_CB *p_ccb, UINT8 *p_reply)
{
    UINT8           *p_start, *p_param_len;
    UINT16          param_len, list_byte_count;
    BOOLEAN         cont_request_needed = FALSE;

#if (SDP_DEBUG_RAW == TRUE)
    SDP_TRACE_WARNING("process_service_attr_rsp raw inc:%d\n",
                      SDP_RAW_DATA_INCLUDED);
#endif
    /* If p_reply is NULL, we were called after the records handles were read */
    if (p_reply) {
#if (SDP_DEBUG_RAW == TRUE)
        SDP_TRACE_WARNING("ID & len: 0x%02x-%02x-%02x-%02x\n",
                          p_reply[0], p_reply[1], p_reply[2], p_reply[3]);
#endif
        /* Skip transaction ID and length */
        p_reply += 4;

        BE_STREAM_TO_UINT16 (list_byte_count, p_reply);
#if (SDP_DEBUG_RAW == TRUE)
        SDP_TRACE_WARNING("list_byte_count:%d\n", list_byte_count);
#endif

        /* Copy the response to the scratchpad. First, a safety check on the length */
        if ((p_ccb->list_len + list_byte_count) > SDP_MAX_LIST_BYTE_COUNT) {
            sdp_disconnect (p_ccb, SDP_INVALID_PDU_SIZE);
            return;
        }

#if (SDP_DEBUG_RAW == TRUE)
        SDP_TRACE_WARNING("list_len: %d, list_byte_count: %d\n",
                          p_ccb->list_len, list_byte_count);
#endif
        if (p_ccb->rsp_list == NULL) {
            p_ccb->rsp_list = (UINT8 *)osi_malloc (SDP_MAX_LIST_BYTE_COUNT);
            if (p_ccb->rsp_list == NULL) {
                SDP_TRACE_ERROR ("SDP - no gki buf to save rsp\n");
                sdp_disconnect (p_ccb, SDP_NO_RESOURCES);
                return;
            }
        }
        memcpy (&p_ccb->rsp_list[p_ccb->list_len], p_reply, list_byte_count);
        p_ccb->list_len += list_byte_count;
        p_reply         += list_byte_count;
#if (SDP_DEBUG_RAW == TRUE)
        SDP_TRACE_WARNING("list_len: %d(attr_rsp)\n", p_ccb->list_len);

        /* Check if we need to request a continuation */
        SDP_TRACE_WARNING("*p_reply:%d(%d)\n", *p_reply, SDP_MAX_CONTINUATION_LEN);
#endif
        if (*p_reply) {
            if (*p_reply > SDP_MAX_CONTINUATION_LEN) {
                sdp_disconnect (p_ccb, SDP_INVALID_CONT_STATE);
                return;
            }
            cont_request_needed = TRUE;
        } else {

#if (SDP_RAW_DATA_INCLUDED == TRUE)
            SDP_TRACE_WARNING("process_service_attr_rsp\n");
            sdp_copy_raw_data (p_ccb, FALSE);
#endif

            /* Save the response in the database. Stop on any error */
            if (!save_attr_seq (p_ccb, &p_ccb->rsp_list[0], &p_ccb->rsp_list[p_ccb->list_len])) {
                sdp_disconnect (p_ccb, SDP_DB_FULL);
                return;
            }
            p_ccb->list_len = 0;
            p_ccb->cur_handle++;
        }
    }

    /* Now, ask for the next handle. Re-use the buffer we just got. */
    if (p_ccb->cur_handle < p_ccb->num_handles) {
        BT_HDR  *p_msg = (BT_HDR *) osi_malloc(SDP_DATA_BUF_SIZE);
        UINT8   *p;

        if (!p_msg) {
            sdp_disconnect (p_ccb, SDP_NO_RESOURCES);
            return;
        }

        p_msg->offset = L2CAP_MIN_OFFSET;
        p = p_start = (UINT8 *)(p_msg + 1) + L2CAP_MIN_OFFSET;

        /* Get all the attributes from the server */
        UINT8_TO_BE_STREAM  (p, SDP_PDU_SERVICE_ATTR_REQ);
        UINT16_TO_BE_STREAM (p, p_ccb->transaction_id);
        p_ccb->transaction_id++;

        /* Skip the length, we need to add it at the end */
        p_param_len = p;
        p += 2;

        UINT32_TO_BE_STREAM (p, p_ccb->handles[p_ccb->cur_handle]);

        /* Max attribute byte count */
        UINT16_TO_BE_STREAM (p, sdp_cb.max_attr_list_size);

        /* If no attribute filters, build a wildcard attribute sequence */
        if (p_ccb->p_db->num_attr_filters) {
            p = sdpu_build_attrib_seq (p, p_ccb->p_db->attr_filters, p_ccb->p_db->num_attr_filters);
        } else {
            p = sdpu_build_attrib_seq (p, NULL, 0);
        }

        /* Was this a continuation request ? */
        if (cont_request_needed) {
            memcpy (p, p_reply, *p_reply + 1);
            p += *p_reply + 1;
        } else {
            UINT8_TO_BE_STREAM (p, 0);
        }

        /* Go back and put the parameter length into the buffer */
        param_len = (UINT16)(p - p_param_len - 2);
        UINT16_TO_BE_STREAM (p_param_len, param_len);

        /* Set the length of the SDP data in the buffer */
        p_msg->len = (UINT16)(p - p_start);


        L2CA_DataWrite (p_ccb->connection_id, p_msg);

        /* Start inactivity timer */
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_SDP, SDP_INACT_TIMEOUT);
    } else {
        sdp_disconnect (p_ccb, SDP_SUCCESS);
        return;
    }
}