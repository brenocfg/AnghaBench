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
struct TYPE_8__ {int /*<<< orphan*/  hflags; } ;
struct TYPE_6__ {int /*<<< orphan*/  nmi_window_exits; } ;
struct TYPE_10__ {TYPE_3__ arch; TYPE_1__ stat; } ;
struct vcpu_svm {TYPE_5__ vcpu; int /*<<< orphan*/  nmi_iret_rip; TYPE_4__* vmcb; } ;
struct TYPE_7__ {unsigned long intercept; } ;
struct TYPE_9__ {TYPE_2__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  HF_IRET_MASK ; 
 unsigned long INTERCEPT_IRET ; 
 int /*<<< orphan*/  VMCB_INTERCEPTS ; 
 int /*<<< orphan*/  kvm_rip_read (TYPE_5__*) ; 
 int /*<<< orphan*/  mark_dirty (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iret_interception(struct vcpu_svm *svm)
{
	++svm->vcpu.stat.nmi_window_exits;
	svm->vmcb->control.intercept &= ~(1UL << INTERCEPT_IRET);
	mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
	svm->vcpu.arch.hflags |= HF_IRET_MASK;
	svm->nmi_iret_rip = kvm_rip_read(&svm->vcpu);
	return 1;
}