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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int tBTM_BLE_STATE_MASK ;
typedef  int UINT8 ;
typedef  int UINT16 ;
struct TYPE_4__ {int cur_states; } ;
struct TYPE_6__ {TYPE_1__ ble_ctr_cb; } ;
struct TYPE_5__ {int /*<<< orphan*/ * (* get_ble_supported_states ) () ;} ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int BTM_BLE_STATE_INVALID ; 
 int BTM_BLE_STATE_SCAN_ADV_BIT ; 
 int /*<<< orphan*/  BTM_LE_STATES_SUPPORTED (int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ btm_cb ; 
 int*** btm_le_state_combo_tbl ; 
 TYPE_2__* controller_get_interface () ; 
 int /*<<< orphan*/ * stub1 () ; 

BOOLEAN btm_ble_topology_check(tBTM_BLE_STATE_MASK request_state_mask)
{
    BOOLEAN rt = FALSE;

    UINT8   state_offset = 0;
    UINT16  cur_states = btm_cb.ble_ctr_cb.cur_states;
    UINT8   mask, offset;
    UINT8   request_state = 0;

    /* check only one bit is set and within valid range */
    if (request_state_mask == BTM_BLE_STATE_INVALID ||
            request_state_mask > BTM_BLE_STATE_SCAN_ADV_BIT ||
            (request_state_mask & (request_state_mask - 1 )) != 0) {
        BTM_TRACE_ERROR("illegal state requested: %d", request_state_mask);
        return rt;
    }

    while (request_state_mask) {
        request_state_mask >>= 1;
        request_state ++;
    }

    /* check if the requested state is supported or not */
    mask = btm_le_state_combo_tbl[0][request_state - 1][0];
    offset = btm_le_state_combo_tbl[0][request_state - 1][1];

    const uint8_t *ble_supported_states = controller_get_interface()->get_ble_supported_states();

    if (!BTM_LE_STATES_SUPPORTED(ble_supported_states, mask, offset)) {
        BTM_TRACE_ERROR("state requested not supported: %d", request_state);
        return rt;
    }

    rt = TRUE;
    /* make sure currently active states are all supported in conjunction with the requested
       state. If the bit in table is not set, the combination is not supported */
    while (cur_states != 0) {
        if (cur_states & 0x01) {
            mask = btm_le_state_combo_tbl[request_state][state_offset][0];
            offset = btm_le_state_combo_tbl[request_state][state_offset][1];

            if (mask != 0 && offset != 0) {
                if (!BTM_LE_STATES_SUPPORTED(ble_supported_states, mask, offset)) {
                    rt = FALSE;
                    break;
                }
            }
        }
        cur_states >>= 1;
        state_offset ++;
    }
    return rt;
}