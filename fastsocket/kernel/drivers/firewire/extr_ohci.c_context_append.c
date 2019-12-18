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
struct descriptor_buffer {int buffer_bus; int used; struct descriptor* buffer; } ;
struct descriptor {int dummy; } ;
struct context {int /*<<< orphan*/  ohci; int /*<<< orphan*/  regs; TYPE_1__* prev; struct descriptor_buffer* buffer_tail; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  branch_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_WAKE ; 
 int /*<<< orphan*/  CONTROL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 TYPE_1__* find_branch_descriptor (struct descriptor*,int) ; 
 int /*<<< orphan*/  flush_writes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_append(struct context *ctx,
			   struct descriptor *d, int z, int extra)
{
	dma_addr_t d_bus;
	struct descriptor_buffer *desc = ctx->buffer_tail;

	d_bus = desc->buffer_bus + (d - desc->buffer) * sizeof(*d);

	desc->used += (z + extra) * sizeof(*d);
	ctx->prev->branch_address = cpu_to_le32(d_bus | z);
	ctx->prev = find_branch_descriptor(d, z);

	reg_write(ctx->ohci, CONTROL_SET(ctx->regs), CONTEXT_WAKE);
	flush_writes(ctx->ohci);
}