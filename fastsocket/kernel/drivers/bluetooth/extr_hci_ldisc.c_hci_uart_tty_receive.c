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
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {scalar_t__ disc_data; } ;
struct hci_uart {int /*<<< orphan*/  rx_lock; TYPE_3__* hdev; TYPE_1__* proto; int /*<<< orphan*/  flags; struct tty_struct* tty; } ;
struct TYPE_5__ {int byte_rx; } ;
struct TYPE_6__ {TYPE_2__ stat; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* recv ) (struct hci_uart*,void*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_UART_PROTO_SET ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hci_uart*,void*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unthrottle (struct tty_struct*) ; 

__attribute__((used)) static void hci_uart_tty_receive(struct tty_struct *tty, const u8 *data, char *flags, int count)
{
	struct hci_uart *hu = (void *)tty->disc_data;

	if (!hu || tty != hu->tty)
		return;

	if (!test_bit(HCI_UART_PROTO_SET, &hu->flags))
		return;

	spin_lock(&hu->rx_lock);
	hu->proto->recv(hu, (void *) data, count);
	hu->hdev->stat.byte_rx += count;
	spin_unlock(&hu->rx_lock);

	tty_unthrottle(tty);
}