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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {int dummy; } ;

/* Variables and functions */
 int cp210x_set_config (struct usb_serial_port*,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static inline int cp210x_set_config_single(struct usb_serial_port *port,
		u8 request, unsigned int data)
{
	return cp210x_set_config(port, request, &data, 2);
}