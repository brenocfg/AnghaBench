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
typedef  int /*<<< orphan*/  lck_grp_attr_t ;
struct TYPE_2__ {unsigned int logical_cpu_max; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_DIAG ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int intr_samplec ; 
 int /*<<< orphan*/ * intr_samplev ; 
 int /*<<< orphan*/ * kalloc_tag (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ kperf_initted ; 
 int kperf_kdebug_init () ; 
 int /*<<< orphan*/  kperf_lck_grp ; 
 int /*<<< orphan*/ * kperf_tid_on_cpus ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ machine_info ; 

int
kperf_init(void)
{
	static lck_grp_attr_t lck_grp_attr;

	unsigned ncpus = 0;
	int err;

	if (kperf_initted) {
		return 0;
	}

	lck_grp_attr_setdefault(&lck_grp_attr);
	lck_grp_init(&kperf_lck_grp, "kperf", &lck_grp_attr);

	ncpus = machine_info.logical_cpu_max;

	/* create buffers to remember which threads don't need to be sampled by PET */
	kperf_tid_on_cpus = kalloc_tag(ncpus * sizeof(*kperf_tid_on_cpus),
	                                  VM_KERN_MEMORY_DIAG);
	if (kperf_tid_on_cpus == NULL) {
		err = ENOMEM;
		goto error;
	}
	bzero(kperf_tid_on_cpus, ncpus * sizeof(*kperf_tid_on_cpus));

	/* create the interrupt buffers */
	intr_samplec = ncpus;
	intr_samplev = kalloc_tag(ncpus * sizeof(*intr_samplev),
	                          VM_KERN_MEMORY_DIAG);
	if (intr_samplev == NULL) {
		err = ENOMEM;
		goto error;
	}
	bzero(intr_samplev, ncpus * sizeof(*intr_samplev));

	/* create kdebug trigger filter buffers */
	if ((err = kperf_kdebug_init())) {
		goto error;
	}

	kperf_initted = TRUE;
	return 0;

error:
	if (intr_samplev) {
		kfree(intr_samplev, ncpus * sizeof(*intr_samplev));
		intr_samplev = NULL;
		intr_samplec = 0;
	}

	if (kperf_tid_on_cpus) {
		kfree(kperf_tid_on_cpus, ncpus * sizeof(*kperf_tid_on_cpus));
		kperf_tid_on_cpus = NULL;
	}

	return err;
}