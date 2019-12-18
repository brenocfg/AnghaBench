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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ BLE_HCI_CMD_HDR_LEN ; 
 scalar_t__ BLE_HCI_UART_H4_CMD ; 
 int BLE_HS_EAGAIN ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ble_hci_trans_buf_free (scalar_t__*) ; 
 int /*<<< orphan*/  esp_vhci_host_check_send_available () ; 
 int /*<<< orphan*/  esp_vhci_host_send_packet (scalar_t__*,scalar_t__) ; 

int ble_hci_trans_hs_cmd_tx(uint8_t *cmd)
{
    uint16_t len;

    assert(cmd != NULL);
    *cmd = BLE_HCI_UART_H4_CMD;
    len = BLE_HCI_CMD_HDR_LEN + cmd[3] + 1;
    if (!esp_vhci_host_check_send_available()) {
        ESP_LOGE(TAG, "Controller not ready to receive packets from host at this time, try again after sometime");
        return BLE_HS_EAGAIN;
    }
    esp_vhci_host_send_packet(cmd, len);

    ble_hci_trans_buf_free(cmd);
    return 0;
}