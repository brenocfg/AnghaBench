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
struct vcpu_svm {TYPE_2__* vmcb; scalar_t__ asid_generation; } ;
struct svm_cpu_data {int next_asid; int max_asid; scalar_t__ asid_generation; } ;
struct TYPE_3__ {int /*<<< orphan*/  asid; int /*<<< orphan*/  tlb_ctl; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLB_CONTROL_FLUSH_ALL_ASID ; 
 int /*<<< orphan*/  VMCB_ASID ; 
 int /*<<< orphan*/  mark_dirty (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void new_asid(struct vcpu_svm *svm, struct svm_cpu_data *svm_data)
{
	if (svm_data->next_asid > svm_data->max_asid) {
		++svm_data->asid_generation;
		svm_data->next_asid = 1;
		svm->vmcb->control.tlb_ctl = TLB_CONTROL_FLUSH_ALL_ASID;
	}

	svm->asid_generation = svm_data->asid_generation;
	svm->vmcb->control.asid = svm_data->next_asid++;

	mark_dirty(svm->vmcb, VMCB_ASID);
}