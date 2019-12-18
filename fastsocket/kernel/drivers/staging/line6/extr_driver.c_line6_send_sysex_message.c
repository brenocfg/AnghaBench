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
struct usb_line6 {int dummy; } ;

/* Variables and functions */
 int SYSEX_EXTRA_SIZE ; 
 int line6_send_raw_message (struct usb_line6*,char const*,int) ; 

int line6_send_sysex_message(struct usb_line6 *line6, const char *buffer,
			     int size)
{
	return line6_send_raw_message(line6, buffer, size + SYSEX_EXTRA_SIZE) - SYSEX_EXTRA_SIZE;
}