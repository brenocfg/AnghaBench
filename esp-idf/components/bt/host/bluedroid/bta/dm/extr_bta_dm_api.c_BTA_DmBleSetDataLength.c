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
typedef  int /*<<< orphan*/  tBTA_SET_PKT_DATA_LENGTH_CBACK ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/ * p_set_pkt_data_cback; int /*<<< orphan*/  tx_data_length; TYPE_1__ hdr; int /*<<< orphan*/  remote_bda; } ;
typedef  TYPE_2__ tBTA_DM_API_BLE_SET_DATA_LENGTH ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_SET_DATA_LENGTH_EVT ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmBleSetDataLength(BD_ADDR remote_device, UINT16 tx_data_length, tBTA_SET_PKT_DATA_LENGTH_CBACK *p_set_pkt_data_cback)
{
    tBTA_DM_API_BLE_SET_DATA_LENGTH *p_msg;

    if ((p_msg = (tBTA_DM_API_BLE_SET_DATA_LENGTH *)osi_malloc(sizeof(tBTA_DM_API_BLE_SET_DATA_LENGTH)))
            != NULL) {
        bdcpy(p_msg->remote_bda, remote_device);
        p_msg->hdr.event = BTA_DM_API_SET_DATA_LENGTH_EVT;
        p_msg->tx_data_length = tx_data_length;
        p_msg->p_set_pkt_data_cback = p_set_pkt_data_cback;

        bta_sys_sendmsg(p_msg);
    }
}