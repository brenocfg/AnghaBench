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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int sec_flags; int /*<<< orphan*/  sm4; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_7__ {scalar_t__ discoverable_mode; } ;
struct TYPE_10__ {scalar_t__ pairing_state; int pairing_flags; int /*<<< orphan*/  connecting_dc; int /*<<< orphan*/  connecting_bda; int /*<<< orphan*/  pairing_bda; TYPE_1__ btm_inq_vars; scalar_t__ connect_only_paired; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* get_is_ready ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_NON_DISCOVERABLE ; 
 int BTM_PAIR_FLAGS_REJECTED_CONNECT ; 
 int BTM_PAIR_FLAGS_WE_STARTED_DD ; 
 scalar_t__ BTM_PAIR_STATE_IDLE ; 
 int BTM_SEC_LINK_KEY_AUTHED ; 
 int /*<<< orphan*/  BTM_SM4_CONN_PEND ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 int /*<<< orphan*/  HCI_ERR_HOST_REJECT_DEVICE ; 
 TYPE_6__ btm_cb ; 
 TYPE_2__* btm_find_dev (int /*<<< orphan*/ *) ; 
 TYPE_2__* btm_sec_alloc_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btsnd_hcic_reject_conn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* controller_get_interface () ; 
 scalar_t__ l2c_link_hci_conn_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

void btm_sec_conn_req (UINT8 *bda, UINT8 *dc)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bda);
    /* Some device may request a connection before we are done with the HCI_Reset sequence */
    if (!controller_get_interface()->get_is_ready()) {
        BTM_TRACE_ERROR ("Security Manager: connect request when device not ready\n");
        btsnd_hcic_reject_conn (bda, HCI_ERR_HOST_REJECT_DEVICE);
        return;
    }

    /* Security guys wants us not to allow connection from not paired devices */

    /* Check if connection is allowed for only paired devices */
    if (btm_cb.connect_only_paired) {
        if (!p_dev_rec || !(p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_AUTHED)) {
            BTM_TRACE_ERROR ("Security Manager: connect request from non-paired device\n");
            btsnd_hcic_reject_conn (bda, HCI_ERR_HOST_REJECT_DEVICE);
            return;
        }
    }

#if BTM_ALLOW_CONN_IF_NONDISCOVER == FALSE
    /* If non-discoverable, only allow known devices to connect */
    if (btm_cb.btm_inq_vars.discoverable_mode == BTM_NON_DISCOVERABLE) {
        if (!p_dev_rec) {
            BTM_TRACE_ERROR ("Security Manager: connect request from not paired device\n");
            btsnd_hcic_reject_conn (bda, HCI_ERR_HOST_REJECT_DEVICE);
            return;
        }
    }
#endif

    if ((btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
            && (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
            && (!memcmp (btm_cb.pairing_bda, bda, BD_ADDR_LEN))) {
        BTM_TRACE_ERROR ("Security Manager: reject connect request from bonding device\n");

        /* incoming connection from bonding device is rejected */
        btm_cb.pairing_flags |= BTM_PAIR_FLAGS_REJECTED_CONNECT;
        btsnd_hcic_reject_conn (bda, HCI_ERR_HOST_REJECT_DEVICE);
        return;
    }

    /* Host is not interested or approved connection.  Save BDA and DC and */
    /* pass request to L2CAP */
    memcpy (btm_cb.connecting_bda, bda, BD_ADDR_LEN);
    memcpy (btm_cb.connecting_dc,  dc,  DEV_CLASS_LEN);

    if (l2c_link_hci_conn_req (bda)) {
        if (!p_dev_rec) {
            /* accept the connection -> allocate a device record */
            p_dev_rec = btm_sec_alloc_dev (bda);
        }
        if (p_dev_rec) {
            p_dev_rec->sm4 |= BTM_SM4_CONN_PEND;
        }
    }
}