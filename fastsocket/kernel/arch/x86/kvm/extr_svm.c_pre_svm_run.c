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
struct vcpu_svm {scalar_t__ asid_generation; } ;
struct svm_cpu_data {scalar_t__ asid_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  new_asid (struct vcpu_svm*,struct svm_cpu_data*) ; 
 struct svm_cpu_data* per_cpu (int /*<<< orphan*/ ,int) ; 
 int raw_smp_processor_id () ; 
 struct svm_cpu_data* svm_data ; 

__attribute__((used)) static void pre_svm_run(struct vcpu_svm *svm)
{
	int cpu = raw_smp_processor_id();

	struct svm_cpu_data *svm_data = per_cpu(svm_data, cpu);

	/* FIXME: handle wraparound of asid_generation */
	if (svm->asid_generation != svm_data->asid_generation)
		new_asid(svm, svm_data);
}