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
typedef  int /*<<< orphan*/  ble_hci_trans_rx_cmd_fn ;
typedef  int /*<<< orphan*/  ble_hci_trans_rx_acl_fn ;

/* Variables and functions */
 void* ble_hci_rx_acl_hs_arg ; 
 int /*<<< orphan*/ * ble_hci_rx_acl_hs_cb ; 
 void* ble_hci_rx_cmd_hs_arg ; 
 int /*<<< orphan*/ * ble_hci_rx_cmd_hs_cb ; 

void ble_hci_trans_cfg_hs(ble_hci_trans_rx_cmd_fn *cmd_cb,
                     void *cmd_arg,
                     ble_hci_trans_rx_acl_fn *acl_cb,
                     void *acl_arg)
{
    ble_hci_rx_cmd_hs_cb = cmd_cb;
    ble_hci_rx_cmd_hs_arg = cmd_arg;
    ble_hci_rx_acl_hs_cb = acl_cb;
    ble_hci_rx_acl_hs_arg = acl_arg;
}