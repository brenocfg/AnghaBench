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
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_4__ {int /*<<< orphan*/  adv_mode; } ;
struct TYPE_5__ {TYPE_1__ inq_var; } ;
struct TYPE_6__ {TYPE_2__ ble_ctr_cb; } ;
typedef  void* BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_ADDR_RANDOM ; 
 scalar_t__ BLE_ADDR_TYPE_ID_BIT ; 
 int /*<<< orphan*/  BLE_CONN_IDLE ; 
 int /*<<< orphan*/  BTM_BLE_ADV_DISABLE ; 
 scalar_t__ BTM_BLE_IS_RESOLVE_BDA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_BLE_RL_ADV ; 
 int /*<<< orphan*/  BTM_BLE_RL_INIT ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 void* FALSE ; 
 int /*<<< orphan*/  HCID_GET_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_ENCRYPT_MODE_DISABLED ; 
 scalar_t__ HCI_ERR_DIRECTED_ADVERTISING_TIMEOUT ; 
 scalar_t__ HCI_ROLE_UNKNOWN ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_connected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*) ; 
 int /*<<< orphan*/  btm_ble_disable_resolving_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_refresh_local_resolvable_private_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_refresh_peer_resolvable_private_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_resolve_random_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  btm_ble_resolve_random_addr_on_conn_cmpl ; 
 int /*<<< orphan*/  btm_ble_set_conn_st (int /*<<< orphan*/ ) ; 
 void* btm_ble_update_mode_operation (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__ btm_cb ; 
 void* btm_identity_addr_to_random_pseudo (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_disconnected (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  l2c_link_hci_disc_comp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  l2cble_conn_comp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* temp_enhanced ; 

void btm_ble_conn_complete(UINT8 *p, UINT16 evt_len, BOOLEAN enhanced)
{
#if (BLE_PRIVACY_SPT == TRUE )
    UINT8       *p_data = p, peer_addr_type;
#endif  ///BLE_PRIVACY_SPT == TRUE
    UINT8       role, status, bda_type;
    UINT16      handle;
    BD_ADDR     bda;
    BD_ADDR     local_rpa, peer_rpa;
    UINT16      conn_interval, conn_latency, conn_timeout;
    BOOLEAN     match = FALSE;
    UNUSED(evt_len);
    STREAM_TO_UINT8   (status, p);
    STREAM_TO_UINT16   (handle, p);
    STREAM_TO_UINT8    (role, p);
    STREAM_TO_UINT8    (bda_type, p);
    STREAM_TO_BDADDR   (bda, p);
    BTM_TRACE_DEBUG("status = %d, handle = %d, role = %d, bda_type = %d",status,handle,role,bda_type);
    if (status == 0) {
        if (enhanced) {
            STREAM_TO_BDADDR   (local_rpa, p);
            STREAM_TO_BDADDR   (peer_rpa, p);
        }
#if (BLE_PRIVACY_SPT == TRUE )
        peer_addr_type = bda_type;
        match = btm_identity_addr_to_random_pseudo (bda, &bda_type, TRUE);

        /* possiblly receive connection complete with resolvable random on
           slave role while the device has been paired */

        /* It will cause that scanner doesn't send scan request to advertiser
        * which has sent IRK to us and we have stored the IRK in controller.
        * It is a hardware limitation. The preliminary solution is not to
        * send key to the controller, but to resolve the random address in host.
        * so we need send the real address information to controller to connect.
        * Once the connection is successful, resolve device address whether it is
        * slave or master*/

        /* if (!match && role == HCI_ROLE_SLAVE && BTM_BLE_IS_RESOLVE_BDA(bda)) { */
        if (!match && BTM_BLE_IS_RESOLVE_BDA(bda)) {
            // save the enhanced value to used in btm_ble_resolve_random_addr_on_conn_cmpl func.
            temp_enhanced = enhanced;
            btm_ble_resolve_random_addr(bda, btm_ble_resolve_random_addr_on_conn_cmpl, p_data);
            // set back the temp enhanced to default after used.
            temp_enhanced = FALSE;
        } else
#endif
        {
            STREAM_TO_UINT16   (conn_interval, p);
            STREAM_TO_UINT16   (conn_latency, p);
            STREAM_TO_UINT16   (conn_timeout, p);
            handle = HCID_GET_HANDLE (handle);

            btm_ble_connected(bda, handle, HCI_ENCRYPT_MODE_DISABLED, role, bda_type, match);
            l2cble_conn_comp (handle, role, bda, bda_type, conn_interval,
                              conn_latency, conn_timeout);

#if (BLE_PRIVACY_SPT == TRUE)
            if (enhanced) {
                btm_ble_refresh_local_resolvable_private_addr(bda, local_rpa);

                if (peer_addr_type & BLE_ADDR_TYPE_ID_BIT) {
                    btm_ble_refresh_peer_resolvable_private_addr(bda, peer_rpa, BLE_ADDR_RANDOM);
                }
            }
#endif
        }
    } else {
        role = HCI_ROLE_UNKNOWN;
        if (status != HCI_ERR_DIRECTED_ADVERTISING_TIMEOUT) {
            btm_ble_set_conn_st(BLE_CONN_IDLE);
#if (defined BLE_PRIVACY_SPT && BLE_PRIVACY_SPT == TRUE)
            btm_ble_disable_resolving_list(BTM_BLE_RL_INIT, TRUE);
#endif
        } else {
#if (defined BLE_PRIVACY_SPT && BLE_PRIVACY_SPT == TRUE)
            btm_cb.ble_ctr_cb.inq_var.adv_mode  = BTM_BLE_ADV_DISABLE;
            btm_ble_disable_resolving_list(BTM_BLE_RL_ADV, TRUE);
#endif
        }

    }

    BOOLEAN bg_con = btm_ble_update_mode_operation(role, bda, status);
    if (status != HCI_SUCCESS && !bg_con) {
        // notify connection failed
        l2c_link_hci_disc_comp (handle, status);
#if (SMP_INCLUDED == TRUE)
        /* Notify security manager */
        btm_sec_disconnected (handle, status);
#endif  ///SMP_INCLUDED == TRUE
    }
}