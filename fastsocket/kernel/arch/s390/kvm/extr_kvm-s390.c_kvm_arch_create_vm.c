#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sca_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {struct sca_block* sca; int /*<<< orphan*/  dbf; TYPE_1__ float_int; } ;
struct kvm {TYPE_2__ arch; } ;
struct TYPE_6__ {int pid; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kvm* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,char*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  debug_register (char*,int,int,int) ; 
 int /*<<< orphan*/  debug_register_view (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_sprintf_view ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvm*) ; 
 struct kvm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int s390_enable_sie () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

struct kvm *kvm_arch_create_vm(void)
{
	struct kvm *kvm;
	int rc;
	char debug_name[16];

	rc = s390_enable_sie();
	if (rc)
		goto out_nokvm;

	rc = -ENOMEM;
	kvm = kzalloc(sizeof(struct kvm), GFP_KERNEL);
	if (!kvm)
		goto out_nokvm;

	kvm->arch.sca = (struct sca_block *) get_zeroed_page(GFP_KERNEL);
	if (!kvm->arch.sca)
		goto out_nosca;

	sprintf(debug_name, "kvm-%u", current->pid);

	kvm->arch.dbf = debug_register(debug_name, 8, 2, 8 * sizeof(long));
	if (!kvm->arch.dbf)
		goto out_nodbf;

	spin_lock_init(&kvm->arch.float_int.lock);
	INIT_LIST_HEAD(&kvm->arch.float_int.list);

	debug_register_view(kvm->arch.dbf, &debug_sprintf_view);
	VM_EVENT(kvm, 3, "%s", "vm created");

	return kvm;
out_nodbf:
	free_page((unsigned long)(kvm->arch.sca));
out_nosca:
	kfree(kvm);
out_nokvm:
	return ERR_PTR(rc);
}