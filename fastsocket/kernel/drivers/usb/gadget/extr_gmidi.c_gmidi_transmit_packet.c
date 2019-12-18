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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct usb_request {unsigned int length; scalar_t__ buf; } ;

/* Variables and functions */

__attribute__((used)) static void gmidi_transmit_packet(struct usb_request *req, uint8_t p0,
					uint8_t p1, uint8_t p2, uint8_t p3)
{
	unsigned length = req->length;
	u8 *buf = (u8 *)req->buf + length;

	buf[0] = p0;
	buf[1] = p1;
	buf[2] = p2;
	buf[3] = p3;
	req->length = length + 4;
}