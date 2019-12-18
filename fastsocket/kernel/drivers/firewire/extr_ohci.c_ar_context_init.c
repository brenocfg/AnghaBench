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
typedef  int /*<<< orphan*/  u32 ;
struct fw_ohci {int dummy; } ;
struct ar_context {TYPE_1__* current_buffer; int /*<<< orphan*/  pointer; int /*<<< orphan*/  tasklet; struct ar_buffer* last_buffer; struct fw_ohci* ohci; int /*<<< orphan*/  regs; } ;
struct ar_buffer {TYPE_1__* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar_context_add_page (struct ar_context*) ; 
 int /*<<< orphan*/  ar_context_tasklet ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ar_context_init(struct ar_context *ctx,
			   struct fw_ohci *ohci, u32 regs)
{
	struct ar_buffer ab;

	ctx->regs        = regs;
	ctx->ohci        = ohci;
	ctx->last_buffer = &ab;
	tasklet_init(&ctx->tasklet, ar_context_tasklet, (unsigned long)ctx);

	ar_context_add_page(ctx);
	ar_context_add_page(ctx);
	ctx->current_buffer = ab.next;
	ctx->pointer = ctx->current_buffer->data;

	return 0;
}