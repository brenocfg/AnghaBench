#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ remote_bd_name; int /*<<< orphan*/  length; } ;
typedef  TYPE_4__ tBTM_REMOTE_DEV_NAME ;
struct TYPE_11__ {int /*<<< orphan*/  event; } ;
struct TYPE_9__ {scalar_t__* bd_name; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_10__ {TYPE_1__ disc_res; } ;
struct TYPE_13__ {TYPE_3__ hdr; TYPE_2__ result; } ;
typedef  TYPE_5__ tBTA_DM_REM_NAME ;
struct TYPE_14__ {scalar_t__ transport; int /*<<< orphan*/  peer_bdaddr; scalar_t__* peer_name; int /*<<< orphan*/  name_discover_done; } ;
typedef  int /*<<< orphan*/  BD_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BCM_STRNCPY_S (char*,int,char*,size_t) ; 
 size_t BD_NAME_LEN ; 
 int /*<<< orphan*/  BTA_DM_REMT_NAME_EVT ; 
 int /*<<< orphan*/  BTM_SecDeleteRmtNameNotifyCallback (int /*<<< orphan*/ *) ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  GAP_BleReadPeerPrefConnParams (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ bta_dm_search_cb ; 
 int /*<<< orphan*/  bta_dm_service_search_remname_cback ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_5__*) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static void bta_dm_remname_cback (tBTM_REMOTE_DEV_NAME *p_remote_name)
{
    tBTA_DM_REM_NAME *p_msg;

    APPL_TRACE_DEBUG("bta_dm_remname_cback len = %d name=<%s>", p_remote_name->length,
                     p_remote_name->remote_bd_name);
    /* remote name discovery is done but it could be failed */
    bta_dm_search_cb.name_discover_done = TRUE;
    BCM_STRNCPY_S((char *)bta_dm_search_cb.peer_name, sizeof(BD_NAME), (char *)p_remote_name->remote_bd_name, (BD_NAME_LEN));
    bta_dm_search_cb.peer_name[BD_NAME_LEN] = 0;

    BTM_SecDeleteRmtNameNotifyCallback(&bta_dm_service_search_remname_cback);

#if BLE_INCLUDED == TRUE && GATTS_INCLUDED == TRUE
    if (bta_dm_search_cb.transport == BT_TRANSPORT_LE ) {
        GAP_BleReadPeerPrefConnParams (bta_dm_search_cb.peer_bdaddr);
    }
#endif

    if ((p_msg = (tBTA_DM_REM_NAME *) osi_malloc(sizeof(tBTA_DM_REM_NAME))) != NULL) {
        bdcpy (p_msg->result.disc_res.bd_addr, bta_dm_search_cb.peer_bdaddr);
        BCM_STRNCPY_S((char *)p_msg->result.disc_res.bd_name, sizeof(BD_NAME), (char *)p_remote_name->remote_bd_name, (BD_NAME_LEN));

        /* make sure the string is null terminated */
        p_msg->result.disc_res.bd_name[BD_NAME_LEN] = 0;

        p_msg->hdr.event = BTA_DM_REMT_NAME_EVT;
        bta_sys_sendmsg(p_msg);
    }
}