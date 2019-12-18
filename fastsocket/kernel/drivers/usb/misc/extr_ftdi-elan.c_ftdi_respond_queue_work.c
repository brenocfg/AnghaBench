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
struct usb_ftdi {int /*<<< orphan*/  kref; int /*<<< orphan*/  respond_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  respond_queue ; 

__attribute__((used)) static void ftdi_respond_queue_work(struct usb_ftdi *ftdi, unsigned int delta)
{
	if (queue_delayed_work(respond_queue, &ftdi->respond_work, delta))
		kref_get(&ftdi->kref);
}