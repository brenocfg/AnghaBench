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
typedef  int /*<<< orphan*/  tGATT_IF ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {int /*<<< orphan*/  scan_param_setup_cback; int /*<<< orphan*/  scan_mode; void* scan_window; void* scan_int; int /*<<< orphan*/  client_if; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_BLE_SCAN_PARAMS ;
typedef  int /*<<< orphan*/  tBLE_SCAN_PARAM_SETUP_CBACK ;
typedef  int /*<<< orphan*/  tBLE_SCAN_MODE ;
typedef  void* UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_BLE_SCAN_PARAM_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmSetBleScanParams(tGATT_IF client_if, UINT32 scan_interval,
                            UINT32 scan_window, tBLE_SCAN_MODE scan_mode,
                            tBLE_SCAN_PARAM_SETUP_CBACK scan_param_setup_cback)
{
    tBTA_DM_API_BLE_SCAN_PARAMS *p_msg;

    if ((p_msg = (tBTA_DM_API_BLE_SCAN_PARAMS *)osi_malloc(sizeof(tBTA_DM_API_BLE_SCAN_PARAMS))) != NULL) {
        memset(p_msg, 0, sizeof(tBTA_DM_API_BLE_SCAN_PARAMS));
        p_msg->hdr.event = BTA_DM_API_BLE_SCAN_PARAM_EVT;
        p_msg->client_if = client_if;
        p_msg->scan_int = scan_interval;
        p_msg->scan_window = scan_window;
        p_msg->scan_mode = scan_mode;
        p_msg->scan_param_setup_cback = scan_param_setup_cback;

        bta_sys_sendmsg(p_msg);
    }
}