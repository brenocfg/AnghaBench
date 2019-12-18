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
typedef  int /*<<< orphan*/  tBTA_DM_BLE_SEL_CBACK ;
typedef  int /*<<< orphan*/  tBTA_DM_BLE_CONN_TYPE ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p_select_cback; int /*<<< orphan*/  bg_conn_type; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_BLE_SET_BG_CONN_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_BLE_SET_BG_CONN_TYPE ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmBleSetBgConnType(tBTA_DM_BLE_CONN_TYPE bg_conn_type, tBTA_DM_BLE_SEL_CBACK *p_select_cback)
{
#if BLE_INCLUDED == TRUE
    tBTA_DM_API_BLE_SET_BG_CONN_TYPE    *p_msg;

    if ((p_msg = (tBTA_DM_API_BLE_SET_BG_CONN_TYPE *) osi_malloc(sizeof(tBTA_DM_API_BLE_SET_BG_CONN_TYPE))) != NULL) {
        memset(p_msg, 0, sizeof(tBTA_DM_API_BLE_SET_BG_CONN_TYPE));

        p_msg->hdr.event        = BTA_DM_API_BLE_SET_BG_CONN_TYPE;
        p_msg->bg_conn_type     = bg_conn_type;
        p_msg->p_select_cback   = p_select_cback;

        bta_sys_sendmsg(p_msg);
    }
#endif
}