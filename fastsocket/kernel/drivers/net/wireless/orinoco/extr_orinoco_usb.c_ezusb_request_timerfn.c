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
typedef  scalar_t__ u_long ;
struct request_context {int killed; int /*<<< orphan*/  refcount; int /*<<< orphan*/  state; TYPE_1__* outurb; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  EZUSB_CTX_REQ_TIMEOUT ; 
 int /*<<< orphan*/  EZUSB_CTX_RESP_TIMEOUT ; 
 int /*<<< orphan*/  URB_ASYNC_UNLINK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  ezusb_ctx_complete (struct request_context*) ; 
 int /*<<< orphan*/  ezusb_request_context_put (struct request_context*) ; 
 int /*<<< orphan*/  usb_unlink_urb (TYPE_1__*) ; 

__attribute__((used)) static void ezusb_request_timerfn(u_long _ctx)
{
	struct request_context *ctx = (void *) _ctx;

	ctx->outurb->transfer_flags |= URB_ASYNC_UNLINK;
	if (usb_unlink_urb(ctx->outurb) == -EINPROGRESS) {
		ctx->state = EZUSB_CTX_REQ_TIMEOUT;
	} else {
		ctx->state = EZUSB_CTX_RESP_TIMEOUT;
		dbg("couldn't unlink");
		atomic_inc(&ctx->refcount);
		ctx->killed = 1;
		ezusb_ctx_complete(ctx);
		ezusb_request_context_put(ctx);
	}
}