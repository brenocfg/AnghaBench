#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_10__ {TYPE_2__ hdr; } ;
typedef  TYPE_3__ tBTA_DM_MSG ;
struct TYPE_8__ {int /*<<< orphan*/  remote_bd_addr; } ;
struct TYPE_12__ {TYPE_1__ results; } ;
struct TYPE_11__ {scalar_t__ services; TYPE_6__* p_btm_inq_info; scalar_t__* peer_name; int /*<<< orphan*/  name_discover_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTA_DM_API_DISCOVER_EVT ; 
 int /*<<< orphan*/  BTA_DM_SEARCH_CMPL_EVT ; 
 TYPE_6__* BTM_InqDbNext (TYPE_6__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bta_dm_discover_device (int /*<<< orphan*/ ) ; 
 TYPE_5__ bta_dm_search_cb ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_3__*) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static void bta_dm_discover_next_device(void)
{

    tBTA_DM_MSG *p_msg;

    APPL_TRACE_DEBUG("bta_dm_discover_next_device");

    /* searching next device on inquiry result */
    if ((bta_dm_search_cb.p_btm_inq_info = BTM_InqDbNext(bta_dm_search_cb.p_btm_inq_info)) != NULL) {
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