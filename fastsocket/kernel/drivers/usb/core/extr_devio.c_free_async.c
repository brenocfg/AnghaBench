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
struct async {int /*<<< orphan*/  mem_usage; TYPE_1__* urb; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {struct async* setup_packet; struct async* transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct async*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usbfs_decrease_memory_usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_async(struct async *as)
{
	put_pid(as->pid);
	kfree(as->urb->transfer_buffer);
	kfree(as->urb->setup_packet);
	usb_free_urb(as->urb);
	usbfs_decrease_memory_usage(as->mem_usage);
	kfree(as);
}