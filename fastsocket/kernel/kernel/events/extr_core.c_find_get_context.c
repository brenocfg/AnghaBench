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
struct task_struct {int flags; int /*<<< orphan*/  perf_event_mutex; scalar_t__* perf_event_ctxp; } ;
struct pmu {int task_ctx_nr; int /*<<< orphan*/  pmu_cpu_context; } ;
struct perf_event_context {int /*<<< orphan*/  pin_count; int /*<<< orphan*/  lock; } ;
struct perf_cpu_context {struct perf_event_context ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct perf_event_context* ERR_PTR (int) ; 
 int ESRCH ; 
 int PF_EXITING ; 
 struct perf_event_context* alloc_perf_context (struct pmu*,struct task_struct*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int /*<<< orphan*/  get_ctx (struct perf_event_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct perf_cpu_context* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 struct perf_event_context* perf_lock_task_context (struct task_struct*,int,unsigned long*) ; 
 scalar_t__ perf_paranoid_cpu () ; 
 int /*<<< orphan*/  put_ctx (struct perf_event_context*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,struct perf_event_context*) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unclone_ctx (struct perf_event_context*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct perf_event_context *
find_get_context(struct pmu *pmu, struct task_struct *task, int cpu)
{
	struct perf_event_context *ctx;
	struct perf_cpu_context *cpuctx;
	unsigned long flags;
	int ctxn, err;

	if (!task) {
		/* Must be root to operate on a CPU event: */
		if (perf_paranoid_cpu() && !capable(CAP_SYS_ADMIN))
			return ERR_PTR(-EACCES);

		/*
		 * We could be clever and allow to attach a event to an
		 * offline CPU and activate it when the CPU comes up, but
		 * that's for later.
		 */
		if (!cpu_online(cpu))
			return ERR_PTR(-ENODEV);

		cpuctx = per_cpu_ptr(pmu->pmu_cpu_context, cpu);
		ctx = &cpuctx->ctx;
		get_ctx(ctx);
		++ctx->pin_count;

		return ctx;
	}

	err = -EINVAL;
	ctxn = pmu->task_ctx_nr;
	if (ctxn < 0)
		goto errout;

retry:
	ctx = perf_lock_task_context(task, ctxn, &flags);
	if (ctx) {
		unclone_ctx(ctx);
		++ctx->pin_count;
		spin_unlock_irqrestore(&ctx->lock, flags);
	} else {
		ctx = alloc_perf_context(pmu, task);
		err = -ENOMEM;
		if (!ctx)
			goto errout;

		err = 0;
		mutex_lock(&task->perf_event_mutex);
		/*
		 * If it has already passed perf_event_exit_task().
		 * we must see PF_EXITING, it takes this mutex too.
		 */
		if (task->flags & PF_EXITING)
			err = -ESRCH;
		else if (task->perf_event_ctxp[ctxn])
			err = -EAGAIN;
		else {
			get_ctx(ctx);
			++ctx->pin_count;
			rcu_assign_pointer(task->perf_event_ctxp[ctxn], ctx);
		}
		mutex_unlock(&task->perf_event_mutex);

		if (unlikely(err)) {
			put_ctx(ctx);

			if (err == -EAGAIN)
				goto retry;
			goto errout;
		}
	}

	return ctx;

errout:
	return ERR_PTR(err);
}