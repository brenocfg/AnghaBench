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
struct kvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct kvm*) ; 
 int PTR_ERR (struct kvm*) ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct kvm*,int /*<<< orphan*/ ) ; 
 struct kvm* kvm_create_vm () ; 
 int /*<<< orphan*/  kvm_put_kvm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_vm_fops ; 

__attribute__((used)) static int kvm_dev_ioctl_create_vm(void)
{
	int fd;
	struct kvm *kvm;

	kvm = kvm_create_vm();
	if (IS_ERR(kvm))
		return PTR_ERR(kvm);
	fd = anon_inode_getfd("kvm-vm", &kvm_vm_fops, kvm, 0);
	if (fd < 0)
		kvm_put_kvm(kvm);

	return fd;
}