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
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_3__ {scalar_t__ rs_disc_pending; scalar_t__ sec_state; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int BTM_GetHCIConnHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 scalar_t__ BTM_SEC_DISC_PENDING ; 
 scalar_t__ BTM_SEC_RS_PENDING ; 
 scalar_t__ BTM_SEC_STATE_DISCONNECTING ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int /*<<< orphan*/  HCI_ERR_PEER_USER ; 
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_disconnect (int,int /*<<< orphan*/ ) ; 

tBTM_STATUS btm_remove_acl (BD_ADDR bd_addr, tBT_TRANSPORT transport)
{
    UINT16  hci_handle = BTM_GetHCIConnHandle(bd_addr, transport);
    tBTM_STATUS status = BTM_SUCCESS;

    BTM_TRACE_DEBUG ("btm_remove_acl\n");
#if BTM_DISC_DURING_RS == TRUE
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bd_addr);

    /* Role Switch is pending, postpone until completed */
    if (p_dev_rec && (p_dev_rec->rs_disc_pending == BTM_SEC_RS_PENDING)) {
        p_dev_rec->rs_disc_pending = BTM_SEC_DISC_PENDING;
    } else  /* otherwise can disconnect right away */
#endif
    {
        if (hci_handle != 0xFFFF && p_dev_rec &&
                p_dev_rec->sec_state != BTM_SEC_STATE_DISCONNECTING) {
            if (!btsnd_hcic_disconnect (hci_handle, HCI_ERR_PEER_USER)) {
                status = BTM_NO_RESOURCES;
            }
        } else {
            status = BTM_UNKNOWN_ADDR;
        }
    }

    return status;
}