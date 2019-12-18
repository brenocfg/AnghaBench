#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {void* supervision_tout; void* slave_latency; void* conn_int_min; void* conn_int_max; int /*<<< orphan*/  peer_bda; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_BLE_CONN_PARAMS ;
typedef  void* UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTA_DM_API_BLE_CONN_PARAM_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmSetBlePrefConnParams(BD_ADDR bd_addr,
                                UINT16 min_conn_int, UINT16 max_conn_int,
                                UINT16 slave_latency, UINT16 supervision_tout )
{
#if BLE_INCLUDED == TRUE
    tBTA_DM_API_BLE_CONN_PARAMS    *p_msg;

    if ((p_msg = (tBTA_DM_API_BLE_CONN_PARAMS *) osi_malloc(sizeof(tBTA_DM_API_BLE_CONN_PARAMS))) != NULL) {
        memset(p_msg, 0, sizeof(tBTA_DM_API_BLE_CONN_PARAMS));

        p_msg->hdr.event = BTA_DM_API_BLE_CONN_PARAM_EVT;

        memcpy(p_msg->peer_bda, bd_addr, BD_ADDR_LEN);

        p_msg->conn_int_max     = max_conn_int;
        p_msg->conn_int_min     = min_conn_int;
        p_msg->slave_latency    = slave_latency;
        p_msg->supervision_tout = supervision_tout;

        bta_sys_sendmsg(p_msg);
    }
#endif
}