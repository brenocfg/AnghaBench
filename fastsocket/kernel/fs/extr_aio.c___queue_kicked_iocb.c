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
struct kioctx {int /*<<< orphan*/  run_list; int /*<<< orphan*/  ctx_lock; } ;
struct kiocb {int /*<<< orphan*/  ki_run_list; struct kioctx* ki_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int __queue_kicked_iocb(struct kiocb *iocb)
{
	struct kioctx *ctx = iocb->ki_ctx;

	assert_spin_locked(&ctx->ctx_lock);

	if (list_empty(&iocb->ki_run_list)) {
		list_add_tail(&iocb->ki_run_list,
			&ctx->run_list);
		return 1;
	}
	return 0;
}