#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  white_list_avail_size; } ;
typedef  TYPE_1__ tBTM_BLE_CB ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_6__ {TYPE_1__ ble_ctr_cb; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_ble_white_list_size ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 TYPE_3__ btm_cb ; 
 TYPE_2__* controller_get_interface () ; 
 int /*<<< orphan*/  stub1 () ; 

void btm_ble_clear_white_list_complete(UINT8 *p_data, UINT16 evt_len)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT8       status;
    UNUSED(evt_len);

    BTM_TRACE_EVENT ("btm_ble_clear_white_list_complete");
    STREAM_TO_UINT8  (status, p_data);

    if (status == HCI_SUCCESS) {
        p_cb->white_list_avail_size = controller_get_interface()->get_ble_white_list_size();
    }
}