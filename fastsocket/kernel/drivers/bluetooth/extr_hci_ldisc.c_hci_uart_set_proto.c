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
struct hci_uart_proto {int (* open ) (struct hci_uart*) ;int /*<<< orphan*/  (* close ) (struct hci_uart*) ;} ;
struct hci_uart {struct hci_uart_proto* proto; } ;

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 struct hci_uart_proto* hci_uart_get_proto (int) ; 
 int hci_uart_register_dev (struct hci_uart*) ; 
 int stub1 (struct hci_uart*) ; 
 int /*<<< orphan*/  stub2 (struct hci_uart*) ; 

__attribute__((used)) static int hci_uart_set_proto(struct hci_uart *hu, int id)
{
	struct hci_uart_proto *p;
	int err;

	p = hci_uart_get_proto(id);
	if (!p)
		return -EPROTONOSUPPORT;

	err = p->open(hu);
	if (err)
		return err;

	hu->proto = p;

	err = hci_uart_register_dev(hu);
	if (err) {
		p->close(hu);
		return err;
	}

	return 0;
}