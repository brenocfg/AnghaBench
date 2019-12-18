#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_API (char*) ; 
 int /*<<< orphan*/  BTA_DM_API_BLE_STOP_ADV_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

extern void BTA_DmBleStopAdvertising(void)
{
    BT_HDR   *p_msg;

    APPL_TRACE_API("BTA_DmBleStopAdvertising\n");

    if ((p_msg = (BT_HDR *) osi_malloc(sizeof(BT_HDR))) != NULL) {
        memset(p_msg, 0, sizeof(BT_HDR));
        p_msg->event = BTA_DM_API_BLE_STOP_ADV_EVT;
        bta_sys_sendmsg(p_msg);
    }
}