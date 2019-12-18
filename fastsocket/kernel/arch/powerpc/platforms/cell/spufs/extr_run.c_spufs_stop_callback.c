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
struct TYPE_2__ {int /*<<< orphan*/  class_1_dar; int /*<<< orphan*/  class_1_dsisr; int /*<<< orphan*/  class_0_dar; int /*<<< orphan*/  class_0_pending; } ;
struct spu_context {int /*<<< orphan*/  stop_wq; TYPE_1__ csa; } ;
struct spu {int /*<<< orphan*/  class_1_dar; int /*<<< orphan*/  class_1_dsisr; int /*<<< orphan*/  class_0_dar; int /*<<< orphan*/  class_0_pending; struct spu_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void spufs_stop_callback(struct spu *spu, int irq)
{
	struct spu_context *ctx = spu->ctx;

	/*
	 * It should be impossible to preempt a context while an exception
	 * is being processed, since the context switch code is specially
	 * coded to deal with interrupts ... But, just in case, sanity check
	 * the context pointer.  It is OK to return doing nothing since
	 * the exception will be regenerated when the context is resumed.
	 */
	if (ctx) {
		/* Copy exception arguments into module specific structure */
		switch(irq) {
		case 0 :
			ctx->csa.class_0_pending = spu->class_0_pending;
			ctx->csa.class_0_dar = spu->class_0_dar;
			break;
		case 1 :
			ctx->csa.class_1_dsisr = spu->class_1_dsisr;
			ctx->csa.class_1_dar = spu->class_1_dar;
			break;
		case 2 :
			break;
		}

		/* ensure that the exception status has hit memory before a
		 * thread waiting on the context's stop queue is woken */
		smp_wmb();

		wake_up_all(&ctx->stop_wq);
	}
}