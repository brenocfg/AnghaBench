#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ con_state; int con_flags; scalar_t__ cur_uuid_idx; scalar_t__ connection_id; int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* p_cb2 ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_cb ) (scalar_t__) ;scalar_t__ disconnect_reason; TYPE_6__* p_db; scalar_t__ cur_handle; } ;
typedef  TYPE_2__ tCONN_CB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_9__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_12__ {int len; TYPE_1__ uu; } ;
struct TYPE_11__ {scalar_t__ num_uuid_filters; scalar_t__ p_first_rec; TYPE_7__* uuid_filters; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CA_DisconnectReq (scalar_t__) ; 
 int SDP_FLAGS_IS_ORIG ; 
 scalar_t__ SDP_FindServiceInDb (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SDP_FindServiceUUIDInDb (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 scalar_t__ SDP_NO_RECS_MATCH ; 
 scalar_t__ SDP_STATE_CONNECTED ; 
 scalar_t__ SDP_STATE_CONN_SETUP ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  SDP_TRACE_EVENT (char*,scalar_t__) ; 
 int /*<<< orphan*/  sdp_disc_connected (TYPE_2__*) ; 
 int /*<<< orphan*/  sdpu_release_ccb (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ) ; 

void sdp_disconnect (tCONN_CB *p_ccb, UINT16 reason)
{
#if (defined(SDP_BROWSE_PLUS) && SDP_BROWSE_PLUS == TRUE)
    /* If we are browsing for multiple UUIDs ... */
    if ((p_ccb->con_state == SDP_STATE_CONNECTED)
            && (p_ccb->con_flags & SDP_FLAGS_IS_ORIG)
            && ((reason == SDP_SUCCESS) || (reason == SDP_NO_RECS_MATCH))) {
        /* If the browse found something, do no more searching */
        if ((p_ccb->cur_uuid_idx == 0) && (p_ccb->p_db->p_first_rec)) {
            p_ccb->cur_uuid_idx = p_ccb->p_db->num_uuid_filters;
        }

        while (++p_ccb->cur_uuid_idx < p_ccb->p_db->num_uuid_filters) {
            /* Check we have not already found the UUID (maybe through browse) */
            if ((p_ccb->p_db->uuid_filters[p_ccb->cur_uuid_idx].len == 2)
                    && (SDP_FindServiceInDb (p_ccb->p_db,
                                             p_ccb->p_db->uuid_filters[p_ccb->cur_uuid_idx].uu.uuid16,
                                             NULL))) {
                continue;
            }

            if ((p_ccb->p_db->uuid_filters[p_ccb->cur_uuid_idx].len > 2)
                    && (SDP_FindServiceUUIDInDb (p_ccb->p_db,
                                                 &p_ccb->p_db->uuid_filters[p_ccb->cur_uuid_idx], NULL))) {
                continue;
            }

            p_ccb->cur_handle = 0;

            SDP_TRACE_EVENT ("SDP - looking for for more,  CID: 0x%x\n",
                             p_ccb->connection_id);

            sdp_disc_connected (p_ccb);
            return;
        }
    }

    if ((reason == SDP_NO_RECS_MATCH) && (p_ccb->p_db->p_first_rec)) {
        reason = SDP_SUCCESS;
    }

#endif

    SDP_TRACE_EVENT ("SDP - disconnect  CID: 0x%x\n", p_ccb->connection_id);

    /* Check if we have a connection ID */
    if (p_ccb->connection_id != 0) {
        L2CA_DisconnectReq (p_ccb->connection_id);
        p_ccb->disconnect_reason = reason;
    }

    /* If at setup state, we may not get callback ind from L2CAP */
    /* Call user callback immediately */
    if (p_ccb->con_state == SDP_STATE_CONN_SETUP) {
        /* Tell the user if he has a callback */
        if (p_ccb->p_cb) {
            (*p_ccb->p_cb) (reason);
        } else if (p_ccb->p_cb2) {
            (*p_ccb->p_cb2) (reason, p_ccb->user_data);
        }

        sdpu_release_ccb (p_ccb);
    }

}