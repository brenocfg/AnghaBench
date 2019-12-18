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
struct task_struct {struct audit_context* audit_context; } ;
struct audit_context {scalar_t__ current_state; int /*<<< orphan*/  prio; int /*<<< orphan*/  ppid; int /*<<< orphan*/  filterkey; scalar_t__ in_syscall; int /*<<< orphan*/  dummy; int /*<<< orphan*/  ctime; int /*<<< orphan*/  argv; int /*<<< orphan*/  major; int /*<<< orphan*/  arch; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; struct audit_context* audit_context; } ;

/* Variables and functions */
 scalar_t__ AUDIT_RECORD_CONTEXT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void audit_finish_fork(struct task_struct *child)
{
	struct audit_context *ctx = current->audit_context;
	struct audit_context *p = child->audit_context;
	if (!p || !ctx)
		return;
	if (!ctx->in_syscall || ctx->current_state != AUDIT_RECORD_CONTEXT)
		return;
	p->arch = ctx->arch;
	p->major = ctx->major;
	memcpy(p->argv, ctx->argv, sizeof(ctx->argv));
	p->ctime = ctx->ctime;
	p->dummy = ctx->dummy;
	p->in_syscall = ctx->in_syscall;
	p->filterkey = kstrdup(ctx->filterkey, GFP_KERNEL);
	p->ppid = current->pid;
	p->prio = ctx->prio;
	p->current_state = ctx->current_state;
}