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
struct utrace_engine {int dummy; } ;
struct task_struct {int dummy; } ;
struct ptrace_context {int /*<<< orphan*/  resume; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int ERESTARTNOINTR ; 
 struct utrace_engine* ERR_PTR (int) ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IS_ERR (struct utrace_engine*) ; 
 int UTRACE_ATTACH_CREATE ; 
 int UTRACE_ATTACH_EXCLUSIVE ; 
 int UTRACE_ATTACH_MATCH_OPS ; 
 int /*<<< orphan*/  UTRACE_RESUME ; 
 int /*<<< orphan*/  kfree (struct ptrace_context*) ; 
 struct ptrace_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct utrace_engine* ptrace_reuse_engine (struct task_struct*) ; 
 int /*<<< orphan*/  ptrace_utrace_ops ; 
 int task_utrace_flags (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 struct utrace_engine* utrace_attach_task (struct task_struct*,int,int /*<<< orphan*/ *,struct ptrace_context*) ; 

__attribute__((used)) static struct utrace_engine *
ptrace_attach_engine(struct task_struct *tracee)
{
	struct utrace_engine *engine;
	struct ptrace_context *ctx;

	if (unlikely(task_utrace_flags(tracee))) {
		engine = ptrace_reuse_engine(tracee);
		if (!IS_ERR(engine) || IS_ERR(engine) == -EPERM)
			return engine;
	}

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (unlikely(!ctx))
		return ERR_PTR(-ENOMEM);

	ctx->resume = UTRACE_RESUME;

	engine = utrace_attach_task(tracee, UTRACE_ATTACH_CREATE |
						UTRACE_ATTACH_EXCLUSIVE |
						UTRACE_ATTACH_MATCH_OPS,
						&ptrace_utrace_ops, ctx);
	if (unlikely(IS_ERR(engine))) {
		if (engine != ERR_PTR(-ESRCH) &&
		    engine != ERR_PTR(-ERESTARTNOINTR))
			engine = ERR_PTR(-EPERM);
		kfree(ctx);
	}

	return engine;
}