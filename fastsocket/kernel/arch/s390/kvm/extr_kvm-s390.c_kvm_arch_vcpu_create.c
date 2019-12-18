#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * cpuflags; int /*<<< orphan*/  wq; TYPE_4__* float_int; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {struct kvm_s390_sie_block* sie_block; TYPE_3__ local_int; } ;
struct kvm_vcpu {TYPE_6__ arch; } ;
struct kvm_s390_sie_block {unsigned int icpua; int /*<<< orphan*/  cpuflags; void* scaol; void* scaoh; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_3__** local_int; } ;
struct TYPE_11__ {TYPE_4__ float_int; TYPE_2__* sca; } ;
struct kvm {TYPE_5__ arch; } ;
typedef  int __u64 ;
typedef  void* __u32 ;
struct TYPE_8__ {TYPE_1__* cpu; } ;
struct TYPE_7__ {int sda; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct kvm_vcpu* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,unsigned int,struct kvm_vcpu*,struct kvm_s390_sie_block*) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kvm_vcpu*) ; 
 int kvm_vcpu_init (struct kvm_vcpu*,struct kvm*,unsigned int) ; 
 struct kvm_vcpu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm,
				      unsigned int id)
{
	struct kvm_vcpu *vcpu = kzalloc(sizeof(struct kvm_vcpu), GFP_KERNEL);
	int rc = -ENOMEM;

	if (!vcpu)
		goto out_nomem;

	vcpu->arch.sie_block = (struct kvm_s390_sie_block *)
					get_zeroed_page(GFP_KERNEL);

	if (!vcpu->arch.sie_block)
		goto out_free_cpu;

	vcpu->arch.sie_block->icpua = id;
	BUG_ON(!kvm->arch.sca);
	if (!kvm->arch.sca->cpu[id].sda)
		kvm->arch.sca->cpu[id].sda = (__u64) vcpu->arch.sie_block;
	vcpu->arch.sie_block->scaoh = (__u32)(((__u64)kvm->arch.sca) >> 32);
	vcpu->arch.sie_block->scaol = (__u32)(__u64)kvm->arch.sca;

	spin_lock_init(&vcpu->arch.local_int.lock);
	INIT_LIST_HEAD(&vcpu->arch.local_int.list);
	vcpu->arch.local_int.float_int = &kvm->arch.float_int;
	spin_lock(&kvm->arch.float_int.lock);
	kvm->arch.float_int.local_int[id] = &vcpu->arch.local_int;
	init_waitqueue_head(&vcpu->arch.local_int.wq);
	vcpu->arch.local_int.cpuflags = &vcpu->arch.sie_block->cpuflags;
	spin_unlock(&kvm->arch.float_int.lock);

	rc = kvm_vcpu_init(vcpu, kvm, id);
	if (rc)
		goto out_free_cpu;
	VM_EVENT(kvm, 3, "create cpu %d at %p, sie block at %p", id, vcpu,
		 vcpu->arch.sie_block);

	return vcpu;
out_free_cpu:
	kfree(vcpu);
out_nomem:
	return ERR_PTR(rc);
}