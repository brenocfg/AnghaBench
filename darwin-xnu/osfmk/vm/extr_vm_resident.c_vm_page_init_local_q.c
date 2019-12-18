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
struct vpl {scalar_t__ vpl_external_count; scalar_t__ vpl_internal_count; scalar_t__ vpl_count; int /*<<< orphan*/  vpl_queue; } ;
struct TYPE_2__ {struct vpl vpl; } ;
struct vplq {TYPE_1__ vpl_un; } ;

/* Variables and functions */
 unsigned int ROUNDUP_NEXTP2 (unsigned int) ; 
 unsigned int VM_PACKED_POINTER_ALIGNMENT ; 
 int /*<<< orphan*/  VPL_LOCK_INIT (struct vpl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kalloc (unsigned int) ; 
 unsigned int ml_get_max_cpus () ; 
 int /*<<< orphan*/  vm_page_lck_attr ; 
 int /*<<< orphan*/  vm_page_lck_grp_local ; 
 struct vplq* vm_page_local_q ; 
 unsigned int vm_page_local_q_count ; 
 int /*<<< orphan*/  vm_page_queue_init (int /*<<< orphan*/ *) ; 

void
vm_page_init_local_q()
{
	unsigned int		num_cpus;
	unsigned int		i;
	struct vplq     	*t_local_q;

	num_cpus = ml_get_max_cpus();

	/*
	 * no point in this for a uni-processor system
	 */
	if (num_cpus >= 2) {
#if KASAN
		/* KASAN breaks the expectation of a size-aligned object by adding a
		 * redzone, so explicitly align. */
		t_local_q = (struct vplq *)kalloc(num_cpus * sizeof(struct vplq) + VM_PACKED_POINTER_ALIGNMENT);
		t_local_q = (void *)(((uintptr_t)t_local_q + (VM_PACKED_POINTER_ALIGNMENT-1)) & ~(VM_PACKED_POINTER_ALIGNMENT-1));
#else
		/* round the size up to the nearest power of two */
		t_local_q = (struct vplq *)kalloc(ROUNDUP_NEXTP2(num_cpus * sizeof(struct vplq)));
#endif

		for (i = 0; i < num_cpus; i++) {
			struct vpl	*lq;

			lq = &t_local_q[i].vpl_un.vpl;
			VPL_LOCK_INIT(lq, &vm_page_lck_grp_local, &vm_page_lck_attr);
			vm_page_queue_init(&lq->vpl_queue);
			lq->vpl_count = 0;
			lq->vpl_internal_count = 0;
			lq->vpl_external_count = 0;
		}
		vm_page_local_q_count = num_cpus;

		vm_page_local_q = (struct vplq *)t_local_q;
	}
}