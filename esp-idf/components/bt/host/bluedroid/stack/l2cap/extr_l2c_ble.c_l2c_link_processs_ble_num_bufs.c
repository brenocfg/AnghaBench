#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT16 ;
struct TYPE_2__ {scalar_t__ controller_le_xmit_window; scalar_t__ num_lm_ble_bufs; int /*<<< orphan*/  num_lm_acl_bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,scalar_t__) ; 
 scalar_t__ L2C_DEF_NUM_BLE_BUF_SHARED ; 
 TYPE_1__ l2cb ; 

void l2c_link_processs_ble_num_bufs (UINT16 num_lm_ble_bufs)
{
    if (num_lm_ble_bufs == 0) {
        num_lm_ble_bufs = L2C_DEF_NUM_BLE_BUF_SHARED;
        l2cb.num_lm_acl_bufs -= L2C_DEF_NUM_BLE_BUF_SHARED;
    }
    L2CAP_TRACE_DEBUG("num_lm_ble_bufs = %d",num_lm_ble_bufs);
    l2cb.num_lm_ble_bufs = l2cb.controller_le_xmit_window = num_lm_ble_bufs;
}