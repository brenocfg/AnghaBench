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
typedef  int /*<<< orphan*/  u8 ;
struct comm_runtime {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb6fire_comm_init_buffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb6fire_comm_send_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb6fire_comm_write8(struct comm_runtime *rt, u8 request,
		u8 reg, u8 value)
{
	u8 buffer[13]; /* 13: maximum length of message */

	usb6fire_comm_init_buffer(buffer, 0x00, request, reg, value, 0x00);
	return usb6fire_comm_send_buffer(buffer, rt->chip->dev);
}