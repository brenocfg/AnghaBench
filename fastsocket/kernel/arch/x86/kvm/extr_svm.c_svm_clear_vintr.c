#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vcpu_svm {TYPE_2__* vmcb; } ;
struct TYPE_3__ {unsigned long long intercept; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned long long INTERCEPT_VINTR ; 
 int /*<<< orphan*/  VMCB_INTERCEPTS ; 
 int /*<<< orphan*/  mark_dirty (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svm_clear_vintr(struct vcpu_svm *svm)
{
	svm->vmcb->control.intercept &= ~(1ULL << INTERCEPT_VINTR);
	mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
}