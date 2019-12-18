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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {scalar_t__ hci_handle; scalar_t__ lmp_version; scalar_t__ manufacturer; scalar_t__ lmp_subversion; scalar_t__ transport; scalar_t__ link_role; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  peer_le_features; scalar_t__ in_use; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_6__ {TYPE_1__* acl_db; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_ble_default_data_packet_txtime ) () ;int /*<<< orphan*/  (* get_ble_default_data_packet_length ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 scalar_t__ HCI_LE_DATA_LEN_EXT_SUPPORTED (int /*<<< orphan*/ ) ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 scalar_t__ HCI_SUCCESS ; 
 int MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_ble_read_remote_feat (scalar_t__) ; 
 int /*<<< orphan*/  btsnd_hcic_ble_set_data_length (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* controller_get_interface () ; 
 int /*<<< orphan*/  l2cble_notify_le_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

void btm_read_remote_version_complete (UINT8 *p)
{
    tACL_CONN        *p_acl_cb = &btm_cb.acl_db[0];
    UINT8             status;
    UINT16            handle;
    int               xx;
    BTM_TRACE_DEBUG ("btm_read_remote_version_complete\n");

    STREAM_TO_UINT8  (status, p);
    STREAM_TO_UINT16 (handle, p);

    /* Look up the connection by handle and copy features */
    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_acl_cb++) {
        if ((p_acl_cb->in_use) && (p_acl_cb->hci_handle == handle)) {
            if (status == HCI_SUCCESS) {
                STREAM_TO_UINT8  (p_acl_cb->lmp_version, p);
                STREAM_TO_UINT16 (p_acl_cb->manufacturer, p);
                STREAM_TO_UINT16 (p_acl_cb->lmp_subversion, p);
            }
#if BLE_INCLUDED == TRUE
            if (p_acl_cb->transport == BT_TRANSPORT_LE) {
                if(p_acl_cb->link_role == HCI_ROLE_MASTER) {
                    if (HCI_LE_DATA_LEN_EXT_SUPPORTED(p_acl_cb->peer_le_features)) {
                        uint16_t data_length = controller_get_interface()->get_ble_default_data_packet_length();
                        uint16_t data_txtime = controller_get_interface()->get_ble_default_data_packet_txtime();
                        btsnd_hcic_ble_set_data_length(p_acl_cb->hci_handle, data_length, data_txtime);
                    }
                    l2cble_notify_le_connection (p_acl_cb->remote_addr);
                } else {
                     //slave role, read remote feature
                     btsnd_hcic_ble_read_remote_feat(p_acl_cb->hci_handle);
                }
            }
#endif
            break;
        }
    }
}