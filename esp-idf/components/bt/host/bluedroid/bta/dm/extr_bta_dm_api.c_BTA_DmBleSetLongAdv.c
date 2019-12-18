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
typedef  int /*<<< orphan*/  tBTA_SET_ADV_DATA_CMPL_CBACK ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  adv_data_len; int /*<<< orphan*/ * adv_data; int /*<<< orphan*/ * p_adv_data_cback; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_SET_LONG_ADV ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_BLE_SET_LONG_ADV_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmBleSetLongAdv (UINT8 *adv_data, UINT32 adv_data_len,
                            tBTA_SET_ADV_DATA_CMPL_CBACK *p_adv_data_cback)
{
    tBTA_DM_API_SET_LONG_ADV  *p_msg;

    if ((p_msg = (tBTA_DM_API_SET_LONG_ADV *)
                 osi_malloc(sizeof(tBTA_DM_API_SET_LONG_ADV))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_BLE_SET_LONG_ADV_EVT;
        p_msg->p_adv_data_cback = p_adv_data_cback;
        p_msg->adv_data = adv_data;
        p_msg->adv_data_len = adv_data_len;

        bta_sys_sendmsg(p_msg);
    }
}