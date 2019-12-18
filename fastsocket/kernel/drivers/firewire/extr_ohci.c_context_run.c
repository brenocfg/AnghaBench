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
typedef  int u32 ;
struct fw_ohci {int dummy; } ;
struct context {int /*<<< orphan*/  regs; TYPE_1__* last; struct fw_ohci* ohci; } ;
struct TYPE_2__ {int /*<<< orphan*/  branch_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_PTR (int /*<<< orphan*/ ) ; 
 int CONTEXT_RUN ; 
 int /*<<< orphan*/  CONTROL_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONTROL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_writes (struct fw_ohci*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void context_run(struct context *ctx, u32 extra)
{
	struct fw_ohci *ohci = ctx->ohci;

	reg_write(ohci, COMMAND_PTR(ctx->regs),
		  le32_to_cpu(ctx->last->branch_address));
	reg_write(ohci, CONTROL_CLEAR(ctx->regs), ~0);
	reg_write(ohci, CONTROL_SET(ctx->regs), CONTEXT_RUN | extra);
	flush_writes(ohci);
}