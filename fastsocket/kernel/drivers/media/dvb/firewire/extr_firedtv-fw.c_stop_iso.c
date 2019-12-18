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
struct firedtv_receive_context {int /*<<< orphan*/  context; int /*<<< orphan*/  buffer; } ;
struct firedtv {struct firedtv_receive_context* backend_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 TYPE_1__* device_of (struct firedtv*) ; 
 int /*<<< orphan*/  fw_iso_buffer_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_context_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_context_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct firedtv_receive_context*) ; 

__attribute__((used)) static void stop_iso(struct firedtv *fdtv)
{
	struct firedtv_receive_context *ctx = fdtv->backend_data;

	fw_iso_context_stop(ctx->context);
	fw_iso_buffer_destroy(&ctx->buffer, device_of(fdtv)->card);
	fw_iso_context_destroy(ctx->context);
	kfree(ctx);
}