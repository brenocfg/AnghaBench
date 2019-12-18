#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {int actual_length; int /*<<< orphan*/  transfer_buffer_length; TYPE_2__* ep; TYPE_1__* dev; struct api_context* context; } ;
struct api_context {int status; int /*<<< orphan*/  done; } ;
struct TYPE_6__ {int /*<<< orphan*/  comm; } ;
struct TYPE_5__ {int /*<<< orphan*/  desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 unsigned long MAX_SCHEDULE_TIMEOUT ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_endpoint_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_urb_dir_in (struct urb*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int usb_start_wait_urb(struct urb *urb, int timeout, int *actual_length)
{
	struct api_context ctx;
	unsigned long expire;
	int retval;

	init_completion(&ctx.done);
	urb->context = &ctx;
	urb->actual_length = 0;
	retval = usb_submit_urb(urb, GFP_NOIO);
	if (unlikely(retval))
		goto out;

	expire = timeout ? msecs_to_jiffies(timeout) : MAX_SCHEDULE_TIMEOUT;
	if (!wait_for_completion_timeout(&ctx.done, expire)) {
		usb_kill_urb(urb);
		retval = (ctx.status == -ENOENT ? -ETIMEDOUT : ctx.status);

		dev_dbg(&urb->dev->dev,
			"%s timed out on ep%d%s len=%u/%u\n",
			current->comm,
			usb_endpoint_num(&urb->ep->desc),
			usb_urb_dir_in(urb) ? "in" : "out",
			urb->actual_length,
			urb->transfer_buffer_length);
	} else
		retval = ctx.status;
out:
	if (actual_length)
		*actual_length = urb->actual_length;

	usb_free_urb(urb);
	return retval;
}