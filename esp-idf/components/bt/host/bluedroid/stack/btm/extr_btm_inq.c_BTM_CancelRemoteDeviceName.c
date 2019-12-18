#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_3__ {int /*<<< orphan*/  remname_bda; scalar_t__ remname_active; } ;
typedef  TYPE_1__ tBTM_INQUIRY_VAR_ST ;
struct TYPE_4__ {TYPE_1__ btm_inq_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*) ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 scalar_t__ BTM_UseLeLink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 scalar_t__ btm_ble_cancel_remote_name (int /*<<< orphan*/ ) ; 
 TYPE_2__ btm_cb ; 
 scalar_t__ btsnd_hcic_rmt_name_req_cancel (int /*<<< orphan*/ ) ; 

tBTM_STATUS  BTM_CancelRemoteDeviceName (void)
{
    tBTM_INQUIRY_VAR_ST *p_inq = &btm_cb.btm_inq_vars;

    BTM_TRACE_API ("BTM_CancelRemoteDeviceName()\n");

    /* Make sure there is not already one in progress */
    if (p_inq->remname_active) {
#if BLE_INCLUDED == TRUE
        if (BTM_UseLeLink(p_inq->remname_bda)) {
            if (btm_ble_cancel_remote_name(p_inq->remname_bda)) {
                return (BTM_CMD_STARTED);
            } else {
                return (BTM_UNKNOWN_ADDR);
            }
        } else
#endif
        {
            if (btsnd_hcic_rmt_name_req_cancel (p_inq->remname_bda)) {
                return (BTM_CMD_STARTED);
            } else {
                return (BTM_NO_RESOURCES);
            }
        }
    } else {
        return (BTM_WRONG_MODE);
    }
}