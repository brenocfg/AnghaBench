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
typedef  void* u16 ;
struct TYPE_2__ {scalar_t__ data; int /*<<< orphan*/  function; } ;
struct request_context {TYPE_1__ timer; int /*<<< orphan*/  done; int /*<<< orphan*/  refcount; void* in_rid; void* out_rid; int /*<<< orphan*/  state; struct ezusb_priv* upriv; struct request_context* buf; int /*<<< orphan*/  outurb; } ;
struct ezusb_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_BUF_SIZE ; 
 int /*<<< orphan*/  EZUSB_CTX_START ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ezusb_request_timerfn ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct request_context*) ; 
 struct request_context* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct request_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct request_context *ezusb_alloc_ctx(struct ezusb_priv *upriv,
					       u16 out_rid, u16 in_rid)
{
	struct request_context *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_ATOMIC);
	if (!ctx)
		return NULL;

	ctx->buf = kmalloc(BULK_BUF_SIZE, GFP_ATOMIC);
	if (!ctx->buf) {
		kfree(ctx);
		return NULL;
	}
	ctx->outurb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!ctx->outurb) {
		kfree(ctx->buf);
		kfree(ctx);
		return NULL;
	}

	ctx->upriv = upriv;
	ctx->state = EZUSB_CTX_START;
	ctx->out_rid = out_rid;
	ctx->in_rid = in_rid;

	atomic_set(&ctx->refcount, 1);
	init_completion(&ctx->done);

	init_timer(&ctx->timer);
	ctx->timer.function = ezusb_request_timerfn;
	ctx->timer.data = (u_long) ctx;
	return ctx;
}