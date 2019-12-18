#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int opcode; int param_len; int /*<<< orphan*/ * p_param_buf; } ;
typedef  TYPE_1__ tBTM_VSC_CMPL ;
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (TYPE_1__*) ;
struct TYPE_8__ {int /*<<< orphan*/  (* update_exceptional_list_cmp_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ tBTM_BLE_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_9__ {TYPE_3__ ble_ctr_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
#define  HCI_VENDOR_BLE_LONG_ADV_DATA 129 
#define  HCI_VENDOR_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST 128 
 int /*<<< orphan*/  STREAM_TO_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__ btm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

void btm_vsc_complete (UINT8 *p, UINT16 opcode, UINT16 evt_len,
                       tBTM_CMPL_CB *p_vsc_cplt_cback)
{
#if (BLE_INCLUDED == TRUE)
    tBTM_BLE_CB *ble_cb = &btm_cb.ble_ctr_cb;
    switch(opcode) {
        case HCI_VENDOR_BLE_LONG_ADV_DATA:
            BTM_TRACE_EVENT("Set long adv data complete\n");
            break;
        case HCI_VENDOR_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST: {
            uint8_t subcode, status; uint32_t length;
            STREAM_TO_UINT8(status, p);
            STREAM_TO_UINT8(subcode, p);
            STREAM_TO_UINT32(length, p);
            if(ble_cb && ble_cb->update_exceptional_list_cmp_cb) {
                (*ble_cb->update_exceptional_list_cmp_cb)(status, subcode, length, p);
            }
            break;
        }
        default:
        break;
    }
    tBTM_VSC_CMPL   vcs_cplt_params;

    /* If there was a callback address for vcs complete, call it */
    if (p_vsc_cplt_cback) {
        /* Pass paramters to the callback function */
        vcs_cplt_params.opcode = opcode;        /* Number of bytes in return info */
        vcs_cplt_params.param_len = evt_len;    /* Number of bytes in return info */
        vcs_cplt_params.p_param_buf = p;
        (*p_vsc_cplt_cback)(&vcs_cplt_params);  /* Call the VSC complete callback function */
    }
#endif
}