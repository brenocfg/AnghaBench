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
struct TYPE_3__ {int /*<<< orphan*/  mpe_mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_BLOCK_SIZE ; 
 int /*<<< orphan*/  BLE_ACL_BUF_COUNT ; 
 int /*<<< orphan*/  BLE_HCI_EVT_BUF_SIZE ; 
 int /*<<< orphan*/  BLE_HCI_EVT_HI_BUF_COUNT ; 
 int /*<<< orphan*/  BLE_HCI_EVT_LO_BUF_COUNT ; 
 int BLE_HCI_TRANS_CMD_SZ ; 
 int MYNEWT_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSINIT_ASSERT_ACTIVE () ; 
 int /*<<< orphan*/  SYSINIT_PANIC_ASSERT (int) ; 
 int /*<<< orphan*/  ble_hci_acl_buf ; 
 int /*<<< orphan*/  ble_hci_acl_mbuf_pool ; 
 TYPE_1__ ble_hci_acl_pool ; 
 int /*<<< orphan*/  ble_hci_cmd_buf ; 
 int /*<<< orphan*/  ble_hci_cmd_pool ; 
 int /*<<< orphan*/  ble_hci_evt_hi_buf ; 
 int /*<<< orphan*/  ble_hci_evt_hi_pool ; 
 int /*<<< orphan*/  ble_hci_evt_lo_buf ; 
 int /*<<< orphan*/  ble_hci_evt_lo_pool ; 
 int os_mbuf_pool_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int os_mempool_ext_init (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int os_mempool_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ble_hci_transport_init(void)
{
    int rc;

    /* Ensure this function only gets called by sysinit. */
    SYSINIT_ASSERT_ACTIVE();

    rc = os_mempool_ext_init(&ble_hci_acl_pool,
                             MYNEWT_VAL(BLE_ACL_BUF_COUNT),
                             ACL_BLOCK_SIZE,
                             ble_hci_acl_buf,
                             "ble_hci_acl_pool");
    SYSINIT_PANIC_ASSERT(rc == 0);

    rc = os_mbuf_pool_init(&ble_hci_acl_mbuf_pool,
                           &ble_hci_acl_pool.mpe_mp,
                           ACL_BLOCK_SIZE,
                           MYNEWT_VAL(BLE_ACL_BUF_COUNT));
    SYSINIT_PANIC_ASSERT(rc == 0);

    /*
     * Create memory pool of HCI command buffers. NOTE: we currently dont
     * allow this to be configured. The controller will only allow one
     * outstanding command. We decided to keep this a pool in case we allow
     * allow the controller to handle more than one outstanding command.
     */
    rc = os_mempool_init(&ble_hci_cmd_pool,
                         1,
                         BLE_HCI_TRANS_CMD_SZ,
                         ble_hci_cmd_buf,
                         "ble_hci_cmd_pool");
    SYSINIT_PANIC_ASSERT(rc == 0);

    rc = os_mempool_init(&ble_hci_evt_hi_pool,
                         MYNEWT_VAL(BLE_HCI_EVT_HI_BUF_COUNT),
                         MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE),
                         ble_hci_evt_hi_buf,
                         "ble_hci_evt_hi_pool");
    SYSINIT_PANIC_ASSERT(rc == 0);

    rc = os_mempool_init(&ble_hci_evt_lo_pool,
                         MYNEWT_VAL(BLE_HCI_EVT_LO_BUF_COUNT),
                         MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE),
                         ble_hci_evt_lo_buf,
                         "ble_hci_evt_lo_pool");
    SYSINIT_PANIC_ASSERT(rc == 0);
}