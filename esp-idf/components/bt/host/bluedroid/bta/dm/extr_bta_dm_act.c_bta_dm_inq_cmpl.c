#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  num_resps; } ;
struct TYPE_17__ {TYPE_1__ inq_cmpl; } ;
typedef  TYPE_5__ tBTA_DM_SEARCH ;
struct TYPE_16__ {int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_14__ {int /*<<< orphan*/  num; } ;
struct TYPE_18__ {TYPE_4__ hdr; TYPE_2__ inq_cmpl; } ;
typedef  TYPE_6__ tBTA_DM_MSG ;
struct TYPE_19__ {scalar_t__ services; TYPE_11__* p_btm_inq_info; scalar_t__* peer_name; int /*<<< orphan*/  name_discover_done; int /*<<< orphan*/  (* p_search_cback ) (int /*<<< orphan*/ ,TYPE_5__*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  remote_bd_addr; } ;
struct TYPE_12__ {TYPE_3__ results; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTA_DM_API_DISCOVER_EVT ; 
 int /*<<< orphan*/  BTA_DM_INQ_CMPL_EVT ; 
 int /*<<< orphan*/  BTA_DM_SEARCH_CMPL_EVT ; 
 TYPE_11__* BTM_InqDbFirst () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bta_dm_discover_device (int /*<<< orphan*/ ) ; 
 TYPE_9__ bta_dm_search_cb ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_6__*) ; 
 scalar_t__ osi_malloc (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_5__*) ; 

void bta_dm_inq_cmpl (tBTA_DM_MSG *p_data)
{
    tBTA_DM_MSG *p_msg;
    tBTA_DM_SEARCH  data;

    APPL_TRACE_DEBUG("bta_dm_inq_cmpl");

    data.inq_cmpl.num_resps = p_data->inq_cmpl.num;
    bta_dm_search_cb.p_search_cback(BTA_DM_INQ_CMPL_EVT, &data);

    if ((bta_dm_search_cb.p_btm_inq_info = BTM_InqDbFirst()) != NULL) {
        /* start name and service discovery from the first device on inquiry result */
        bta_dm_search_cb.name_discover_done = FALSE;
        bta_dm_search_cb.peer_name[0]       = 0;
#if (SDP_INCLUDED == TRUE)
        bta_dm_discover_device(bta_dm_search_cb.p_btm_inq_info->results.remote_bd_addr);
#endif  ///SDP_INCLUDED == TRUE
    } else {
        /* no devices, search complete */
        bta_dm_search_cb.services = 0;

        if ((p_msg = (tBTA_DM_MSG *) osi_malloc(sizeof(tBTA_DM_MSG))) != NULL) {
            p_msg->hdr.event          = BTA_DM_SEARCH_CMPL_EVT;
            p_msg->hdr.layer_specific = BTA_DM_API_DISCOVER_EVT;
            bta_sys_sendmsg(p_msg);
        }
    }
}