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
struct i1480u {int /*<<< orphan*/ * rx_skb; TYPE_1__* rx_buf; } ;
struct TYPE_2__ {scalar_t__ urb; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int i1480u_RX_BUFS ; 
 int /*<<< orphan*/  usb_free_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

void i1480u_rx_release(struct i1480u *i1480u)
{
	int cnt;
	for (cnt = 0; cnt < i1480u_RX_BUFS; cnt++) {
		if (i1480u->rx_buf[cnt].data)
			dev_kfree_skb(i1480u->rx_buf[cnt].data);
		if (i1480u->rx_buf[cnt].urb) {
			usb_kill_urb(i1480u->rx_buf[cnt].urb);
			usb_free_urb(i1480u->rx_buf[cnt].urb);
		}
	}
	if (i1480u->rx_skb != NULL)
		dev_kfree_skb(i1480u->rx_skb);
}