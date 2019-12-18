#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int shadow_efer; } ;
struct TYPE_10__ {TYPE_1__ arch; } ;
struct vcpu_svm {TYPE_4__ vcpu; TYPE_3__* vmcb; } ;
struct TYPE_8__ {scalar_t__ cpl; } ;
struct TYPE_9__ {TYPE_2__ save; } ;

/* Variables and functions */
 int EFER_SVME ; 
 int /*<<< orphan*/  UD_VECTOR ; 
 int /*<<< orphan*/  is_paging (TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_inject_gp (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_exception (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nested_svm_check_permissions(struct vcpu_svm *svm)
{
	if (!(svm->vcpu.arch.shadow_efer & EFER_SVME)
	    || !is_paging(&svm->vcpu)) {
		kvm_queue_exception(&svm->vcpu, UD_VECTOR);
		return 1;
	}

	if (svm->vmcb->save.cpl) {
		kvm_inject_gp(&svm->vcpu, 0);
		return 1;
	}

       return 0;
}