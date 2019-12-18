#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned long long intercept; int exit_required; } ;
struct TYPE_6__ {int hflags; } ;
struct TYPE_7__ {TYPE_1__ arch; } ;
struct vcpu_svm {TYPE_5__ nested; TYPE_4__* vmcb; TYPE_2__ vcpu; } ;
struct TYPE_8__ {int /*<<< orphan*/  exit_code; } ;
struct TYPE_9__ {TYPE_3__ control; } ;

/* Variables and functions */
 int HF_HIF_MASK ; 
 int HF_VINTR_MASK ; 
 int /*<<< orphan*/  SVM_EXIT_INTR ; 
 int /*<<< orphan*/  is_nested (struct vcpu_svm*) ; 
 int /*<<< orphan*/  nsvm_printk (char*) ; 

__attribute__((used)) static inline int nested_svm_intr(struct vcpu_svm *svm)
{
	if (!is_nested(svm))
		return 0;

	if (!(svm->vcpu.arch.hflags & HF_VINTR_MASK))
		return 0;

	if (!(svm->vcpu.arch.hflags & HF_HIF_MASK))
		return 0;

	svm->vmcb->control.exit_code = SVM_EXIT_INTR;

	if (svm->nested.intercept & 1ULL) {
		/*
		 * The #vmexit can't be emulated here directly because this
		 * code path runs with irqs and preemtion disabled. A
		 * #vmexit emulation might sleep. Only signal request for
		 * the #vmexit here.
		 */
		svm->nested.exit_required = true;
		nsvm_printk("VMexit -> INTR\n");
		return 1;
	}

	return 0;
}