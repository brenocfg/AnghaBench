#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct os_mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_ACL_BUF_SIZE ; 
 int /*<<< orphan*/  BLE_HCI_DATA_HDR_SZ ; 
 int /*<<< orphan*/  MYNEWT_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_ENTER_CRITICAL (int) ; 
 int /*<<< orphan*/  OS_EXIT_CRITICAL (int) ; 
 int /*<<< orphan*/  ble_hci_rx_acl_hs_cb (struct os_mbuf*,int /*<<< orphan*/ *) ; 
 struct os_mbuf* ble_hci_trans_acl_buf_alloc () ; 
 scalar_t__ os_mbuf_append (struct os_mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_mbuf_free_chain (struct os_mbuf*) ; 

__attribute__((used)) static void ble_hci_rx_acl(uint8_t *data, uint16_t len)
{
    struct os_mbuf *m;
    int sr;
    if (len < BLE_HCI_DATA_HDR_SZ || len > MYNEWT_VAL(BLE_ACL_BUF_SIZE)) {
        return;
    }

    m = ble_hci_trans_acl_buf_alloc();

    if (!m) {
        return;
    }
    if (os_mbuf_append(m, data, len)) {
        os_mbuf_free_chain(m);
        return;
    }
    OS_ENTER_CRITICAL(sr);
    if (ble_hci_rx_acl_hs_cb) {
        ble_hci_rx_acl_hs_cb(m, NULL);
    }
    OS_EXIT_CRITICAL(sr);
}