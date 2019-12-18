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
struct ptrace_context {int options; int stop_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_EVENT_SYSCALL ; 
 int PTRACE_O_TRACESYSGOOD ; 
 int /*<<< orphan*/  set_stop_code (struct ptrace_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_syscall_code(struct ptrace_context *ctx)
{
	set_stop_code(ctx, PTRACE_EVENT_SYSCALL);
	if (ctx->options & PTRACE_O_TRACESYSGOOD)
		ctx->stop_code |= 0x80;
}