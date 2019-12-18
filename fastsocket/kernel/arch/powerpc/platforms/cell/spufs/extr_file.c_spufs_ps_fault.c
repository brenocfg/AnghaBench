#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vm_fault {unsigned long pgoff; scalar_t__ virtual_address; } ;
struct vm_area_struct {TYPE_1__* vm_file; } ;
struct spu_context {scalar_t__ state; TYPE_3__* spu; int /*<<< orphan*/  run_wq; } ;
struct TYPE_9__ {TYPE_2__* mm; } ;
struct TYPE_8__ {unsigned long problem_phys; } ;
struct TYPE_7__ {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_6__ {struct spu_context* private_data; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ SPU_STATE_RUNNABLE ; 
 scalar_t__ SPU_STATE_SAVED ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_SIGBUS ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ fatal_signal_pending (TYPE_4__*) ; 
 int /*<<< orphan*/  get_spu_context (struct spu_context*) ; 
 int /*<<< orphan*/  put_spu_context (struct spu_context*) ; 
 scalar_t__ spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_context_nospu_trace (int /*<<< orphan*/ ,struct spu_context*) ; 
 int /*<<< orphan*/  spu_context_trace (int /*<<< orphan*/ ,struct spu_context*,TYPE_3__*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 int /*<<< orphan*/  spufs_ps_fault__enter ; 
 int /*<<< orphan*/  spufs_ps_fault__insert ; 
 int /*<<< orphan*/  spufs_ps_fault__sleep ; 
 int /*<<< orphan*/  spufs_ps_fault__wake ; 
 int spufs_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_insert_pfn (struct vm_area_struct*,unsigned long,unsigned long) ; 

__attribute__((used)) static int spufs_ps_fault(struct vm_area_struct *vma,
				    struct vm_fault *vmf,
				    unsigned long ps_offs,
				    unsigned long ps_size)
{
	struct spu_context *ctx = vma->vm_file->private_data;
	unsigned long area, offset = vmf->pgoff << PAGE_SHIFT;
	int ret = 0;

	spu_context_nospu_trace(spufs_ps_fault__enter, ctx);

	if (offset >= ps_size)
		return VM_FAULT_SIGBUS;

	if (fatal_signal_pending(current))
		return VM_FAULT_SIGBUS;

	/*
	 * Because we release the mmap_sem, the context may be destroyed while
	 * we're in spu_wait. Grab an extra reference so it isn't destroyed
	 * in the meantime.
	 */
	get_spu_context(ctx);

	/*
	 * We have to wait for context to be loaded before we have
	 * pages to hand out to the user, but we don't want to wait
	 * with the mmap_sem held.
	 * It is possible to drop the mmap_sem here, but then we need
	 * to return VM_FAULT_NOPAGE because the mappings may have
	 * hanged.
	 */
	if (spu_acquire(ctx))
		goto refault;

	if (ctx->state == SPU_STATE_SAVED) {
		up_read(&current->mm->mmap_sem);
		spu_context_nospu_trace(spufs_ps_fault__sleep, ctx);
		ret = spufs_wait(ctx->run_wq, ctx->state == SPU_STATE_RUNNABLE);
		spu_context_trace(spufs_ps_fault__wake, ctx, ctx->spu);
		down_read(&current->mm->mmap_sem);
	} else {
		area = ctx->spu->problem_phys + ps_offs;
		vm_insert_pfn(vma, (unsigned long)vmf->virtual_address,
					(area + offset) >> PAGE_SHIFT);
		spu_context_trace(spufs_ps_fault__insert, ctx, ctx->spu);
	}

	if (!ret)
		spu_release(ctx);

refault:
	put_spu_context(ctx);
	return VM_FAULT_NOPAGE;
}