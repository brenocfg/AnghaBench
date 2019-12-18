#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_SCO_DATA_FLAG ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_data_cb ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_1__ sco_cb; } ;
struct TYPE_8__ {int offset; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HCID_GET_EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCID_GET_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  UNUSED (scalar_t__) ; 
 TYPE_6__ btm_cb ; 
 int /*<<< orphan*/  btm_find_scb_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

void  btm_route_sco_data(BT_HDR *p_msg)
{
#if BTM_SCO_HCI_INCLUDED == TRUE
    UINT16      sco_inx, handle;
    UINT8       *p = (UINT8 *)(p_msg + 1) + p_msg->offset;
    UINT8       pkt_size = 0;
    UINT8       pkt_status = 0;

    /* Extract Packet_Status_Flag and handle */
    STREAM_TO_UINT16 (handle, p);
    pkt_status = HCID_GET_EVENT(handle);
    handle   = HCID_GET_HANDLE (handle);

    STREAM_TO_UINT8 (pkt_size, p);
    UNUSED(pkt_size);
    if ((sco_inx = btm_find_scb_by_handle(handle)) != BTM_MAX_SCO_LINKS ) {
        /* send data callback */
        if (!btm_cb.sco_cb.p_data_cb )
            /* if no data callback registered,  just free the buffer  */
        {
            osi_free (p_msg);
        } else {
            (*btm_cb.sco_cb.p_data_cb)(sco_inx, p_msg, (tBTM_SCO_DATA_FLAG) pkt_status);
        }
    } else { /* no mapping handle SCO connection is active, free the buffer */
        osi_free (p_msg);
    }
    BTM_TRACE_DEBUG ("SCO: hdl %x, len %d, pkt_sz %d\n", handle, p_msg->len, pkt_size);
#else
    osi_free(p_msg);
#endif
}