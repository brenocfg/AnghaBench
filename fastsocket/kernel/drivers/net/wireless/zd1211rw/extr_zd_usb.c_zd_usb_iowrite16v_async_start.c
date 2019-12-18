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
struct zd_usb {int in_async; int /*<<< orphan*/ * urb_async_waiting; scalar_t__ cmd_error; int /*<<< orphan*/  submitted_cmds; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_ASSERT (int) ; 
 int mutex_is_locked (int /*<<< orphan*/ *) ; 
 int usb_anchor_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* zd_usb_to_chip (struct zd_usb*) ; 

void zd_usb_iowrite16v_async_start(struct zd_usb *usb)
{
	ZD_ASSERT(usb_anchor_empty(&usb->submitted_cmds));
	ZD_ASSERT(usb->urb_async_waiting == NULL);
	ZD_ASSERT(!usb->in_async);

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));

	usb->in_async = 1;
	usb->cmd_error = 0;
	usb->urb_async_waiting = NULL;
}