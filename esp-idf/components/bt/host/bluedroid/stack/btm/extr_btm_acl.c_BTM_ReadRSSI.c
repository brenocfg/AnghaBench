#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  void* tBTM_STATUS ;
struct TYPE_11__ {void* status; } ;
typedef  TYPE_2__ tBTM_RSSI_RESULTS ;
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (TYPE_2__*) ;
struct TYPE_12__ {int /*<<< orphan*/  hci_handle; } ;
typedef  TYPE_4__ tACL_CONN ;
struct TYPE_10__ {int /*<<< orphan*/  rssi_timer; int /*<<< orphan*/  (* p_rssi_cmpl_cb ) (TYPE_2__*) ;} ;
struct TYPE_13__ {TYPE_1__ devcb; } ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 void* BTM_BUSY ; 
 void* BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_DEV_REPLY_TIMEOUT ; 
 void* BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* BTM_UNKNOWN_ADDR ; 
 int /*<<< orphan*/  BTU_TTYPE_BTM_ACL ; 
 TYPE_4__* btm_bda_to_acl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_read_rssi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

tBTM_STATUS BTM_ReadRSSI (BD_ADDR remote_bda, tBT_TRANSPORT transport, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;

    BTM_TRACE_API ("BTM_ReadRSSI: RemBdAddr: %02x%02x%02x%02x%02x%02x\n",
                   remote_bda[0], remote_bda[1], remote_bda[2],
                   remote_bda[3], remote_bda[4], remote_bda[5]);
    tBTM_RSSI_RESULTS result;
    /* If someone already waiting on the version, do not allow another */
    if (btm_cb.devcb.p_rssi_cmpl_cb) {
        result.status = BTM_BUSY;
        (*p_cb)(&result);
        return (BTM_BUSY);
    }

    p = btm_bda_to_acl(remote_bda, transport);
    if (p != (tACL_CONN *)NULL) {
        btu_start_timer (&btm_cb.devcb.rssi_timer, BTU_TTYPE_BTM_ACL,
                         BTM_DEV_REPLY_TIMEOUT);

        btm_cb.devcb.p_rssi_cmpl_cb = p_cb;

        if (!btsnd_hcic_read_rssi (p->hci_handle)) {
            btm_cb.devcb.p_rssi_cmpl_cb = NULL;
            btu_stop_timer (&btm_cb.devcb.rssi_timer);
            result.status = BTM_NO_RESOURCES;
            (*p_cb)(&result);
            return (BTM_NO_RESOURCES);
        } else {
            return (BTM_CMD_STARTED);
        }
    }

    /* If here, no BD Addr found */
    return (BTM_UNKNOWN_ADDR);
}