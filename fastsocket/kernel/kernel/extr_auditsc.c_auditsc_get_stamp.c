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
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct audit_context {unsigned int serial; int prio; int /*<<< orphan*/  current_state; TYPE_1__ ctime; int /*<<< orphan*/  in_syscall; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_RECORD_CONTEXT ; 
 unsigned int audit_serial () ; 

int auditsc_get_stamp(struct audit_context *ctx,
		       struct timespec *t, unsigned int *serial)
{
	if (!ctx->in_syscall)
		return 0;
	if (!ctx->serial)
		ctx->serial = audit_serial();
	t->tv_sec  = ctx->ctime.tv_sec;
	t->tv_nsec = ctx->ctime.tv_nsec;
	*serial    = ctx->serial;
	if (!ctx->prio) {
		ctx->prio = 1;
		ctx->current_state = AUDIT_RECORD_CONTEXT;
	}
	return 1;
}