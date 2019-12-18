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
typedef  int /*<<< orphan*/  tBTM_SP_EVT_DATA ;
struct TYPE_8__ {int* bd_addr; int* dev_class; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ tBTM_SP_COMPLT ;
struct TYPE_9__ {scalar_t__ sec_state; int /*<<< orphan*/  hci_handle; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  sec_flags; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
typedef  scalar_t__ UINT8 ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_sp_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {TYPE_1__ api; int /*<<< orphan*/  pairing_tle; int /*<<< orphan*/  pairing_bda; int /*<<< orphan*/  pairing_state; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_ERR_PROCESSING ; 
 int /*<<< orphan*/  BTM_PAIR_STATE_WAIT_DISCONNECT ; 
 int /*<<< orphan*/  BTM_SEC_AUTHENTICATED ; 
 scalar_t__ BTM_SEC_STATE_AUTHENTICATING ; 
 int /*<<< orphan*/  BTM_SP_COMPLT_EVT ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BTU_TTYPE_USER_FUNC ; 
 int /*<<< orphan*/  BT_1SEC_TIMEOUT ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HCI_ERR_AUTH_FAILURE ; 
 scalar_t__ HCI_ERR_CONN_CAUSE_LOCAL_HOST ; 
 scalar_t__ HCI_ERR_PAIRING_NOT_ALLOWED ; 
 scalar_t__ HCI_ERR_PEER_USER ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int*,scalar_t__*) ; 
 scalar_t__ TRUE ; 
 TYPE_6__ btm_cb ; 
 TYPE_3__* btm_find_dev (int*) ; 
 int /*<<< orphan*/  btm_pair_state_descr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_send_hci_disconnect (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btm_simple_pair_complete (UINT8 *p)
{
    tBTM_SP_COMPLT  evt_data;
    tBTM_SEC_DEV_REC *p_dev_rec;
    UINT8           status;
    BOOLEAN         disc = FALSE;

    status = *p++;
    STREAM_TO_BDADDR (evt_data.bd_addr, p);

    if ((p_dev_rec = btm_find_dev (evt_data.bd_addr)) == NULL) {
        BTM_TRACE_ERROR ("btm_simple_pair_complete() with unknown BDA: %08x%04x\n",
                         (evt_data.bd_addr[0] << 24) + (evt_data.bd_addr[1] << 16) + (evt_data.bd_addr[2] << 8) + evt_data.bd_addr[3],
                         (evt_data.bd_addr[4] << 8) + evt_data.bd_addr[5]);
        return;
    }
#if (BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE)
    BTM_TRACE_EVENT ("btm_simple_pair_complete()  Pair State: %s  Status:%d  sec_state: %u\n",
                     btm_pair_state_descr(btm_cb.pairing_state),  status, p_dev_rec->sec_state);
#endif  ///BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE
    evt_data.status = BTM_ERR_PROCESSING;
    if (status == HCI_SUCCESS) {
        evt_data.status = BTM_SUCCESS;
        p_dev_rec->sec_flags |= BTM_SEC_AUTHENTICATED;
    } else {
        if (status == HCI_ERR_PAIRING_NOT_ALLOWED) {
            /* The test spec wants the peer device to get this failure code. */
            btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_DISCONNECT);

            /* Change the timer to 1 second */
            btu_start_timer (&btm_cb.pairing_tle, BTU_TTYPE_USER_FUNC, BT_1SEC_TIMEOUT);
        } else if (memcmp (btm_cb.pairing_bda, evt_data.bd_addr, BD_ADDR_LEN) == 0) {
            /* stop the timer */
            btu_stop_timer (&btm_cb.pairing_tle);

            if (p_dev_rec->sec_state != BTM_SEC_STATE_AUTHENTICATING) {
                /* the initiating side: will receive auth complete event. disconnect ACL at that time */
                disc = TRUE;
            }
        } else {
            disc = TRUE;
        }
    }

    /* Let the pairing state stay active, p_auth_complete_callback will report the failure */
    memcpy (evt_data.bd_addr, p_dev_rec->bd_addr, BD_ADDR_LEN);
    memcpy (evt_data.dev_class, p_dev_rec->dev_class, DEV_CLASS_LEN);

    if (btm_cb.api.p_sp_callback) {
        (*btm_cb.api.p_sp_callback) (BTM_SP_COMPLT_EVT, (tBTM_SP_EVT_DATA *)&evt_data);
    }

    if (disc) {
        /* simple pairing failed */
        /* Avoid sending disconnect on HCI_ERR_PEER_USER */
        if ((status != HCI_ERR_PEER_USER) && (status != HCI_ERR_CONN_CAUSE_LOCAL_HOST)) {
            btm_sec_send_hci_disconnect (p_dev_rec, HCI_ERR_AUTH_FAILURE, p_dev_rec->hci_handle);
        }
    }
}