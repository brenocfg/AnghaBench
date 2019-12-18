#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  transport; int /*<<< orphan*/ * p_bda; } ;
struct TYPE_6__ {TYPE_1__ conn; int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ tBTM_BL_EVENT_DATA ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_bl_changed_cb ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BL_COLLISION_EVT ; 
 int /*<<< orphan*/  BTM_INVALID_HCI_HANDLE ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

BOOLEAN  btm_acl_notif_conn_collision (BD_ADDR bda)
{
    tBTM_BL_EVENT_DATA  evt_data;

    /* Report possible collision to the upper layer. */
    if (btm_cb.p_bl_changed_cb) {
        BTM_TRACE_DEBUG ("btm_acl_notif_conn_collision: RemBdAddr: %02x%02x%02x%02x%02x%02x\n",
                         bda[0], bda[1], bda[2], bda[3], bda[4], bda[5]);

        evt_data.event = BTM_BL_COLLISION_EVT;
        evt_data.conn.p_bda = bda;

#if BLE_INCLUDED == TRUE
        evt_data.conn.transport = BT_TRANSPORT_BR_EDR;
        evt_data.conn.handle = BTM_INVALID_HCI_HANDLE;
#endif
        (*btm_cb.p_bl_changed_cb)(&evt_data);
        return TRUE;
    } else {
        return FALSE;
    }
}