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

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  BT_INFO (char*) ; 
 int /*<<< orphan*/  bcsp ; 
 int hci_uart_register_proto (int /*<<< orphan*/ *) ; 

int bcsp_init(void)
{
	int err = hci_uart_register_proto(&bcsp);

	if (!err)
		BT_INFO("HCI BCSP protocol initialized");
	else
		BT_ERR("HCI BCSP protocol registration failed");

	return err;
}