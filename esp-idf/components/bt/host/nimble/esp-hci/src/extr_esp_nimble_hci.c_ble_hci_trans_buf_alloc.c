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

/* Variables and functions */
#define  BLE_HCI_TRANS_BUF_CMD 130 
#define  BLE_HCI_TRANS_BUF_EVT_HI 129 
#define  BLE_HCI_TRANS_BUF_EVT_LO 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ble_hci_cmd_pool ; 
 int /*<<< orphan*/  ble_hci_evt_hi_pool ; 
 int /*<<< orphan*/  ble_hci_evt_lo_pool ; 
 int /*<<< orphan*/ * os_memblock_get (int /*<<< orphan*/ *) ; 

uint8_t *ble_hci_trans_buf_alloc(int type)
{
    uint8_t *buf;

    switch (type) {
    case BLE_HCI_TRANS_BUF_CMD:
        buf = os_memblock_get(&ble_hci_cmd_pool);
        break;

    case BLE_HCI_TRANS_BUF_EVT_HI:
        buf = os_memblock_get(&ble_hci_evt_hi_pool);
        if (buf == NULL) {
            /* If no high-priority event buffers remain, try to grab a
             * low-priority one.
             */
            buf = ble_hci_trans_buf_alloc(BLE_HCI_TRANS_BUF_EVT_LO);
        }
        break;

    case BLE_HCI_TRANS_BUF_EVT_LO:
        buf = os_memblock_get(&ble_hci_evt_lo_pool);
        break;

    default:
        assert(0);
        buf = NULL;
    }

    return buf;
}