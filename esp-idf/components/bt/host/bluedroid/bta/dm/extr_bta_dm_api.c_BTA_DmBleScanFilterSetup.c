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
typedef  int /*<<< orphan*/ * tBTA_DM_BLE_REF_VALUE ;
typedef  int /*<<< orphan*/  tBTA_DM_BLE_PF_PARAM_CBACK ;
typedef  int /*<<< orphan*/  tBTA_DM_BLE_PF_FILT_PARAMS ;
typedef  int /*<<< orphan*/ * tBTA_DM_BLE_PF_FILT_INDEX ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p_target; int /*<<< orphan*/ * ref_value; int /*<<< orphan*/ * p_filt_param_cback; int /*<<< orphan*/  filt_params; int /*<<< orphan*/ * filt_index; int /*<<< orphan*/ * action; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_SCAN_FILTER_PARAM_SETUP ;
typedef  int /*<<< orphan*/  tBLE_BD_ADDR ;
typedef  int /*<<< orphan*/ * UINT8 ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_API (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTA_DM_API_SCAN_FILTER_SETUP_EVT ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmBleScanFilterSetup(UINT8 action, tBTA_DM_BLE_PF_FILT_INDEX filt_index,
                              tBTA_DM_BLE_PF_FILT_PARAMS *p_filt_params,
                              tBLE_BD_ADDR *p_target,
                              tBTA_DM_BLE_PF_PARAM_CBACK *p_cmpl_cback,
                              tBTA_DM_BLE_REF_VALUE ref_value)
{
#if BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE
    tBTA_DM_API_SCAN_FILTER_PARAM_SETUP *p_msg;
    APPL_TRACE_API ("BTA_DmBleScanFilterSetup: %d", action);

    UINT16  len = sizeof(tBTA_DM_API_SCAN_FILTER_PARAM_SETUP) + sizeof(tBLE_BD_ADDR);

    if ((p_msg = (tBTA_DM_API_SCAN_FILTER_PARAM_SETUP *) osi_malloc(len)) != NULL) {
        memset (p_msg, 0, len);

        p_msg->hdr.event        = BTA_DM_API_SCAN_FILTER_SETUP_EVT;
        p_msg->action       = action;
        p_msg->filt_index = filt_index;
        if (p_filt_params) {
            memcpy(&p_msg->filt_params, p_filt_params, sizeof(tBTA_DM_BLE_PF_FILT_PARAMS));
        }
        p_msg->p_filt_param_cback = p_cmpl_cback;
        p_msg->ref_value        = ref_value;

        if (p_target) {
            p_msg->p_target = (tBLE_BD_ADDR *)(p_msg + 1);
            memcpy(p_msg->p_target, p_target, sizeof(tBLE_BD_ADDR));
        }

        bta_sys_sendmsg(p_msg);
    }
#else
    UNUSED(action);
    UNUSED(filt_index);
    UNUSED(p_filt_params);
    UNUSED(p_target);
    UNUSED(p_cmpl_cback);
    UNUSED(ref_value);
#endif
}