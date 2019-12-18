#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int io_cap; int oob_data; int auth_req; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_2__ tBTM_SP_IO_RSP ;
typedef  int /*<<< orphan*/  tBTM_SP_EVT_DATA ;
struct TYPE_8__ {int rmt_io_caps; int rmt_auth_req; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  trusted_mask; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_6__ {int /*<<< orphan*/  (* p_sp_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {scalar_t__ pairing_state; TYPE_1__ api; int /*<<< orphan*/  pairing_flags; int /*<<< orphan*/  connecting_dc; int /*<<< orphan*/  connecting_bda; int /*<<< orphan*/  pairing_bda; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int BTM_AUTH_DD_BOND ; 
 int /*<<< orphan*/  BTM_PAIR_FLAGS_PEER_STARTED_DD ; 
 scalar_t__ BTM_PAIR_STATE_IDLE ; 
 scalar_t__ BTM_PAIR_STATE_INCOMING_SSP ; 
 int /*<<< orphan*/  BTM_SEC_CLR_TRUSTED_DEVICE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_SP_IO_RSP_EVT ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int,int /*<<< orphan*/ *) ; 
 TYPE_5__ btm_cb ; 
 TYPE_3__* btm_find_or_alloc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_inq_stop_on_ssp () ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (scalar_t__) ; 
 int /*<<< orphan*/  l2c_pin_code_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btm_io_capabilities_rsp (UINT8 *p)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    tBTM_SP_IO_RSP evt_data;

    STREAM_TO_BDADDR (evt_data.bd_addr, p);
    STREAM_TO_UINT8 (evt_data.io_cap, p);
    STREAM_TO_UINT8 (evt_data.oob_data, p);
    STREAM_TO_UINT8 (evt_data.auth_req, p);

    /* Allocate a new device record or reuse the oldest one */
    p_dev_rec = btm_find_or_alloc_dev (evt_data.bd_addr);

    /* If no security is in progress, this indicates incoming security */
    if (btm_cb.pairing_state == BTM_PAIR_STATE_IDLE) {
        memcpy (btm_cb.pairing_bda, evt_data.bd_addr, BD_ADDR_LEN);

        btm_sec_change_pairing_state (BTM_PAIR_STATE_INCOMING_SSP);

        /* Make sure we reset the trusted mask to help against attacks */
        BTM_SEC_CLR_TRUSTED_DEVICE(p_dev_rec->trusted_mask);

        /* work around for FW bug */
        btm_inq_stop_on_ssp();
    }

    /* Notify L2CAP to increase timeout */
    l2c_pin_code_request (evt_data.bd_addr);

    /* We must have a device record here.
     * Use the connecting device's CoD for the connection */
    /* coverity[uninit_use_in_call]
    Event uninit_use_in_call: Using uninitialized element of array "evt_data.bd_addr" in call to function "memcmp"
    FALSE-POSITIVE error from Coverity test-tool. evt_data.bd_addr is set at the beginning with:     STREAM_TO_BDADDR (evt_data.bd_addr, p);
    */
    if (!memcmp (evt_data.bd_addr, btm_cb.connecting_bda, BD_ADDR_LEN)) {
        memcpy (p_dev_rec->dev_class, btm_cb.connecting_dc, DEV_CLASS_LEN);
    }

    /* peer sets dedicated bonding bit and we did not initiate dedicated bonding */
    if (btm_cb.pairing_state == BTM_PAIR_STATE_INCOMING_SSP /* peer initiated bonding */
            && (evt_data.auth_req & BTM_AUTH_DD_BOND) ) {          /* and dedicated bonding bit is set */
        btm_cb.pairing_flags |= BTM_PAIR_FLAGS_PEER_STARTED_DD;
    }

    /* save the IO capability in the device record */
    p_dev_rec->rmt_io_caps  = evt_data.io_cap;
    p_dev_rec->rmt_auth_req = evt_data.auth_req;

    if (btm_cb.api.p_sp_callback) {
        (*btm_cb.api.p_sp_callback) (BTM_SP_IO_RSP_EVT, (tBTM_SP_EVT_DATA *)&evt_data);
    }
}