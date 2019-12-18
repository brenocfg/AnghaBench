#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ num_handles; int /*<<< orphan*/  disc_state; int /*<<< orphan*/ * handles; } ;
typedef  TYPE_1__ tCONN_CB ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_8__ {scalar_t__ max_recs_per_search; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_STREAM_TO_UINT16 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT32 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  SDP_DISC_WAIT_ATTR ; 
 int /*<<< orphan*/  SDP_INVALID_CONT_STATE ; 
 scalar_t__ SDP_MAX_CONTINUATION_LEN ; 
 int /*<<< orphan*/  SDP_NO_RECS_MATCH ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  process_service_attr_rsp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_4__ sdp_cb ; 
 int /*<<< orphan*/  sdp_disconnect (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_snd_service_search_req (TYPE_1__*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static void process_service_search_rsp (tCONN_CB *p_ccb, UINT8 *p_reply)
{
    UINT16      xx;
    UINT16      total, cur_handles, orig;
    UINT8       cont_len;

    /* Skip transaction, and param len */
    p_reply += 4;
    BE_STREAM_TO_UINT16 (total, p_reply);
    BE_STREAM_TO_UINT16 (cur_handles, p_reply);

    orig = p_ccb->num_handles;
    p_ccb->num_handles += cur_handles;
    if (p_ccb->num_handles == 0) {
        SDP_TRACE_WARNING ("SDP - Rcvd ServiceSearchRsp, no matches\n");
        sdp_disconnect (p_ccb, SDP_NO_RECS_MATCH);
        return;
    }

    /* Save the handles that match. We will can only process a certain number. */
    if (total > sdp_cb.max_recs_per_search) {
        total = sdp_cb.max_recs_per_search;
    }
    if (p_ccb->num_handles > sdp_cb.max_recs_per_search) {
        p_ccb->num_handles = sdp_cb.max_recs_per_search;
    }

    for (xx = orig; xx < p_ccb->num_handles; xx++) {
        BE_STREAM_TO_UINT32 (p_ccb->handles[xx], p_reply);
    }

    BE_STREAM_TO_UINT8 (cont_len, p_reply);
    if (cont_len != 0) {
        if (cont_len > SDP_MAX_CONTINUATION_LEN) {
            sdp_disconnect (p_ccb, SDP_INVALID_CONT_STATE);
            return;
        }
        /* stay in the same state */
        sdp_snd_service_search_req(p_ccb, cont_len, p_reply);
    } else {
        /* change state */
        p_ccb->disc_state = SDP_DISC_WAIT_ATTR;

        /* Kick off the first attribute request */
        process_service_attr_rsp (p_ccb, NULL);
    }
}