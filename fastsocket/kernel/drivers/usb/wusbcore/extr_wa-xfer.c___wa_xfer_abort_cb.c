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
struct wa_xfer_abort_buffer {int /*<<< orphan*/  urb; } ;
struct urb {struct wa_xfer_abort_buffer* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_put_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __wa_xfer_abort_cb(struct urb *urb)
{
	struct wa_xfer_abort_buffer *b = urb->context;
	usb_put_urb(&b->urb);
}