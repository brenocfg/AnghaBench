#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t cur_uuid_idx; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  connection_id; int /*<<< orphan*/  disc_state; TYPE_1__* p_db; scalar_t__ transaction_id; } ;
typedef  TYPE_2__ tCONN_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_11__ {scalar_t__ max_recs_per_search; } ;
struct TYPE_10__ {int offset; scalar_t__ len; } ;
struct TYPE_8__ {int num_uuid_filters; int /*<<< orphan*/ * uuid_filters; } ;
typedef  TYPE_3__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_SDP ; 
 int L2CAP_MIN_OFFSET ; 
 int /*<<< orphan*/  L2CA_DataWrite (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  SDP_DATA_BUF_SIZE ; 
 int /*<<< orphan*/  SDP_DISC_WAIT_HANDLES ; 
 int /*<<< orphan*/  SDP_INACT_TIMEOUT ; 
 int /*<<< orphan*/  SDP_NO_RESOURCES ; 
 int /*<<< orphan*/  SDP_PDU_SERVICE_SEARCH_REQ ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT16_TO_BE_STREAM (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  UINT8_TO_BE_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 
 TYPE_6__ sdp_cb ; 
 int /*<<< orphan*/  sdp_disconnect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sdpu_build_uuid_seq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdp_snd_service_search_req(tCONN_CB *p_ccb, UINT8 cont_len, UINT8 *p_cont)
{
    UINT8           *p, *p_start, *p_param_len;
    BT_HDR          *p_cmd;
    UINT16          param_len;

    /* Get a buffer to send the packet to L2CAP */
    if ((p_cmd = (BT_HDR *) osi_malloc(SDP_DATA_BUF_SIZE)) == NULL) {
        sdp_disconnect (p_ccb, SDP_NO_RESOURCES);
        return;
    }

    p_cmd->offset = L2CAP_MIN_OFFSET;
    p = p_start = (UINT8 *)(p_cmd + 1) + L2CAP_MIN_OFFSET;

    /* Build a service search request packet */
    UINT8_TO_BE_STREAM  (p, SDP_PDU_SERVICE_SEARCH_REQ);
    UINT16_TO_BE_STREAM (p, p_ccb->transaction_id);
    p_ccb->transaction_id++;

    /* Skip the length, we need to add it at the end */
    p_param_len = p;
    p += 2;

    /* Build the UID sequence. */
#if (defined(SDP_BROWSE_PLUS) && SDP_BROWSE_PLUS == TRUE)
    p = sdpu_build_uuid_seq (p, 1, &p_ccb->p_db->uuid_filters[p_ccb->cur_uuid_idx]);
#else
    p = sdpu_build_uuid_seq (p, p_ccb->p_db->num_uuid_filters, p_ccb->p_db->uuid_filters);
#endif

    /* Set max service record count */
    UINT16_TO_BE_STREAM (p, sdp_cb.max_recs_per_search);

    /* Set continuation state */
    UINT8_TO_BE_STREAM (p, cont_len);

    /* if this is not the first request */
    if (cont_len && p_cont) {
        memcpy(p, p_cont, cont_len);
        p += cont_len;
    }

    /* Go back and put the parameter length into the buffer */
    param_len = (UINT16)(p - p_param_len - 2);
    UINT16_TO_BE_STREAM (p_param_len, param_len);

    p_ccb->disc_state = SDP_DISC_WAIT_HANDLES;

    /* Set the length of the SDP data in the buffer */
    p_cmd->len = (UINT16)(p - p_start);

#if (SDP_DEBUG_RAW == TRUE)
    SDP_TRACE_WARNING("sdp_snd_service_search_req cont_len :%d disc_state:%d\n", cont_len, p_ccb->disc_state);
#endif


    L2CA_DataWrite (p_ccb->connection_id, p_cmd);

    /* Start inactivity timer */
    btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_SDP, SDP_INACT_TIMEOUT);

}