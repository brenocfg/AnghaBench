#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_TRANSPORT ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/ * read_rssi_cb; int /*<<< orphan*/  transport; int /*<<< orphan*/  remote_addr; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_READ_RSSI ;
typedef  int /*<<< orphan*/  tBTA_CMPL_CB ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_BLE_READ_RSSI_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmBleReadRSSI(BD_ADDR remote_addr, tBTA_TRANSPORT transport, tBTA_CMPL_CB *cmpl_cb)
{
    tBTA_DM_API_READ_RSSI *p_msg;
    if ((p_msg = (tBTA_DM_API_READ_RSSI *)osi_malloc(sizeof(tBTA_DM_API_READ_RSSI))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_BLE_READ_RSSI_EVT;
        memcpy(p_msg->remote_addr, remote_addr, sizeof(BD_ADDR));
        p_msg->transport = transport;
        p_msg->read_rssi_cb = cmpl_cb;
        bta_sys_sendmsg(p_msg);
    }
}