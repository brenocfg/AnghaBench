#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_3__ {int sec_state; scalar_t__ hci_handle; scalar_t__ ble_hci_handle; scalar_t__ rs_disc_pending; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 scalar_t__ BTM_SEC_DISC_PENDING ; 
 scalar_t__ BTM_SEC_RS_PENDING ; 
#define  BTM_SEC_STATE_DISCONNECTING 130 
#define  BTM_SEC_STATE_DISCONNECTING_BLE 129 
#define  BTM_SEC_STATE_DISCONNECTING_BOTH 128 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  btsnd_hcic_disconnect (scalar_t__,int) ; 

__attribute__((used)) static tBTM_STATUS btm_sec_send_hci_disconnect (tBTM_SEC_DEV_REC *p_dev_rec, UINT8 reason, UINT16 conn_handle)
{
    UINT8       old_state = p_dev_rec->sec_state;
    tBTM_STATUS status = BTM_CMD_STARTED;

    BTM_TRACE_EVENT ("btm_sec_send_hci_disconnect:  handle:0x%x, reason=0x%x\n",
                     conn_handle, reason);

    /* send HCI_Disconnect on a transport only once */
    switch (old_state) {
    case BTM_SEC_STATE_DISCONNECTING:
        if (conn_handle == p_dev_rec->hci_handle) {
            return status;
        }

        p_dev_rec->sec_state = BTM_SEC_STATE_DISCONNECTING_BOTH;
        break;

#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
    case BTM_SEC_STATE_DISCONNECTING_BLE:
        if (conn_handle == p_dev_rec->ble_hci_handle) {
            return status;
        }

        p_dev_rec->sec_state = BTM_SEC_STATE_DISCONNECTING_BOTH;
        break;

    case BTM_SEC_STATE_DISCONNECTING_BOTH:
        return status;
#endif

    default:
        p_dev_rec->sec_state = (conn_handle == p_dev_rec->hci_handle) ?
                               BTM_SEC_STATE_DISCONNECTING : BTM_SEC_STATE_DISCONNECTING_BLE;

        break;
    }

    /* If a role switch is in progress, delay the HCI Disconnect to avoid controller problem */
    if (p_dev_rec->rs_disc_pending == BTM_SEC_RS_PENDING && p_dev_rec->hci_handle == conn_handle) {
        BTM_TRACE_DEBUG("RS in progress - Set DISC Pending flag in btm_sec_send_hci_disconnect to delay disconnect\n");
        p_dev_rec->rs_disc_pending = BTM_SEC_DISC_PENDING;
        status = BTM_SUCCESS;
    }
    /* Tear down the HCI link */
    else if (!btsnd_hcic_disconnect (conn_handle, reason)) {
        /* could not send disconnect. restore old state */
        p_dev_rec->sec_state = old_state;
        status = BTM_NO_RESOURCES;
    }

    return status;
}