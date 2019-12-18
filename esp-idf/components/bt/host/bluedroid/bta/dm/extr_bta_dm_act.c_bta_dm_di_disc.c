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
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSDP_DISCOVERY_DB ;
struct TYPE_9__ {scalar_t__ offset; int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  p_sdp_db; int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  p_cback; } ;
struct TYPE_10__ {TYPE_2__ hdr; TYPE_1__ di_disc; } ;
typedef  TYPE_3__ tBTA_DM_MSG ;
typedef  scalar_t__ UINT16 ;
struct TYPE_12__ {int /*<<< orphan*/  p_di_db; } ;
struct TYPE_11__ {int /*<<< orphan*/  peer_bdaddr; int /*<<< orphan*/ * p_sdp_db; int /*<<< orphan*/  p_search_cback; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTA_DM_API_DI_DISCOVER_EVT ; 
 int BTA_DM_SDP_DB_SIZE ; 
 int /*<<< orphan*/  BTA_DM_SEARCH_CMPL_EVT ; 
 scalar_t__ BTA_FAILURE ; 
 scalar_t__ BTA_SUCCESS ; 
 scalar_t__ SDP_DiDiscover (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ bta_dm_di_cb ; 
 int /*<<< orphan*/  bta_dm_di_disc_callback ; 
 TYPE_5__ bta_dm_search_cb ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_3__*) ; 
 scalar_t__ osi_malloc (int) ; 

void bta_dm_di_disc (tBTA_DM_MSG *p_data)
{
    UINT16  result = BTA_FAILURE;
    tBTA_DM_MSG *p_msg;

    bta_dm_search_cb.p_search_cback = p_data->di_disc.p_cback;
    bdcpy(bta_dm_search_cb.peer_bdaddr, p_data->di_disc.bd_addr);
    bta_dm_di_cb.p_di_db = p_data->di_disc.p_sdp_db;

    if ((bta_dm_search_cb.p_sdp_db = (tSDP_DISCOVERY_DB *)osi_malloc(BTA_DM_SDP_DB_SIZE)) != NULL) {
        if ( SDP_DiDiscover(bta_dm_search_cb.peer_bdaddr, p_data->di_disc.p_sdp_db,
                            p_data->di_disc.len, bta_dm_di_disc_callback) == SDP_SUCCESS) {
            result = BTA_SUCCESS;
        }
    } else {
        APPL_TRACE_ERROR("No buffer to start DI discovery");
    }

    if ( result == BTA_FAILURE &&
            (p_msg = (tBTA_DM_MSG *) osi_malloc(sizeof(tBTA_DM_MSG))) != NULL) {
        p_msg->hdr.event            = BTA_DM_SEARCH_CMPL_EVT;
        p_msg->hdr.layer_specific   = BTA_DM_API_DI_DISCOVER_EVT;
        p_data->hdr.offset          = result;
        bta_sys_sendmsg(p_msg);
    }
}