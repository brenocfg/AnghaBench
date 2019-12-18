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
typedef  int u32 ;
struct context {int /*<<< orphan*/  regs; int /*<<< orphan*/  ohci; } ;

/* Variables and functions */
 int CONTEXT_ACTIVE ; 
 int /*<<< orphan*/  CONTEXT_RUN ; 
 int /*<<< orphan*/  CONTROL_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONTROL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_writes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_error (char*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_stop(struct context *ctx)
{
	u32 reg;
	int i;

	reg_write(ctx->ohci, CONTROL_CLEAR(ctx->regs), CONTEXT_RUN);
	flush_writes(ctx->ohci);

	for (i = 0; i < 10; i++) {
		reg = reg_read(ctx->ohci, CONTROL_SET(ctx->regs));
		if ((reg & CONTEXT_ACTIVE) == 0)
			return;

		mdelay(1);
	}
	fw_error("Error: DMA context still active (0x%08x)\n", reg);
}