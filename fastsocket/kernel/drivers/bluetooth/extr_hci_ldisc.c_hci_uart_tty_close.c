#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/ * disc_data; } ;
struct hci_uart {TYPE_1__* proto; int /*<<< orphan*/  flags; struct hci_dev* hdev; } ;
struct hci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct hci_uart*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*) ; 
 int /*<<< orphan*/  HCI_UART_PROTO_SET ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_uart_close (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct hci_uart*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_uart_tty_close(struct tty_struct *tty)
{
	struct hci_uart *hu = (void *)tty->disc_data;

	BT_DBG("tty %p", tty);

	/* Detach from the tty */
	tty->disc_data = NULL;

	if (hu) {
		struct hci_dev *hdev = hu->hdev;

		if (hdev)
			hci_uart_close(hdev);

		if (test_and_clear_bit(HCI_UART_PROTO_SET, &hu->flags)) {
			hu->proto->close(hu);
			hci_unregister_dev(hdev);
			hci_free_dev(hdev);
		}
	}
}