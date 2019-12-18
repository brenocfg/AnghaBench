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
struct i1480u {TYPE_1__* rx_buf; } ;
struct TYPE_2__ {scalar_t__ urb; } ;

/* Variables and functions */
 int i1480u_RX_BUFS ; 
 int /*<<< orphan*/  usb_unlink_urb (scalar_t__) ; 

__attribute__((used)) static
void i1480u_rx_unlink_urbs(struct i1480u *i1480u)
{
	int cnt;
	for (cnt = 0; cnt < i1480u_RX_BUFS; cnt++) {
		if (i1480u->rx_buf[cnt].urb)
			usb_unlink_urb(i1480u->rx_buf[cnt].urb);
	}
}