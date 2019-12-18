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
struct dvb_usb_adapter {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int usb_urb_exit (int /*<<< orphan*/ *) ; 

int dvb_usb_adapter_stream_exit(struct dvb_usb_adapter *adap)
{
	return usb_urb_exit(&adap->stream);
}