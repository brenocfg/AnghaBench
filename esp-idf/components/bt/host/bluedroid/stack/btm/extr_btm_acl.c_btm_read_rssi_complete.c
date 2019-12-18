#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ hci_status; scalar_t__ rssi; int /*<<< orphan*/  status; int /*<<< orphan*/  rem_bda; } ;
typedef  TYPE_2__ tBTM_RSSI_RESULTS ;
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (TYPE_2__*) ;
struct TYPE_9__ {scalar_t__ hci_handle; int /*<<< orphan*/  remote_addr; scalar_t__ in_use; } ;
typedef  TYPE_4__ tACL_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_rssi_cmpl_cb ) (TYPE_2__*) ;int /*<<< orphan*/  rssi_timer; } ;
struct TYPE_10__ {TYPE_1__ devcb; TYPE_4__* acl_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_ERR_PROCESSING ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 scalar_t__ HCI_SUCCESS ; 
 scalar_t__ MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_6__ btm_cb ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void btm_read_rssi_complete (UINT8 *p)
{
    tBTM_CMPL_CB            *p_cb = btm_cb.devcb.p_rssi_cmpl_cb;
    tBTM_RSSI_RESULTS        results;
    UINT16                   handle;
    tACL_CONN               *p_acl_cb = &btm_cb.acl_db[0];
    UINT16                   index;
    BTM_TRACE_DEBUG ("btm_read_rssi_complete\n");
    btu_stop_timer (&btm_cb.devcb.rssi_timer);

    /* If there was a callback registered for read rssi, call it */
    btm_cb.devcb.p_rssi_cmpl_cb = NULL;

    if (p_cb) {
        STREAM_TO_UINT8  (results.hci_status, p);

        if (results.hci_status == HCI_SUCCESS) {
            results.status = BTM_SUCCESS;

            STREAM_TO_UINT16 (handle, p);

            STREAM_TO_UINT8 (results.rssi, p);
            BTM_TRACE_DEBUG ("BTM RSSI Complete: rssi %d, hci status 0x%02x\n",
                             results.rssi, results.hci_status);

            /* Search through the list of active channels for the correct BD Addr */
            for (index = 0; index < MAX_L2CAP_LINKS; index++, p_acl_cb++) {
                if ((p_acl_cb->in_use) && (handle == p_acl_cb->hci_handle)) {
                    memcpy (results.rem_bda, p_acl_cb->remote_addr, BD_ADDR_LEN);
                    break;
                }
            }
        } else {
            results.status = BTM_ERR_PROCESSING;
        }

        (*p_cb)(&results);
    }
}