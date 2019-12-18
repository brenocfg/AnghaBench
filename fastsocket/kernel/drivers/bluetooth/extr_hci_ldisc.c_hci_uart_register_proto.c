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
struct hci_uart_proto {size_t id; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 size_t HCI_UART_MAX_PROTO ; 
 struct hci_uart_proto** hup ; 

int hci_uart_register_proto(struct hci_uart_proto *p)
{
	if (p->id >= HCI_UART_MAX_PROTO)
		return -EINVAL;

	if (hup[p->id])
		return -EEXIST;

	hup[p->id] = p;

	return 0;
}