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
struct inode {int dummy; } ;
struct file {struct kvm* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_irqfd_release (struct kvm*) ; 
 int /*<<< orphan*/  kvm_put_kvm (struct kvm*) ; 

__attribute__((used)) static int kvm_vm_release(struct inode *inode, struct file *filp)
{
	struct kvm *kvm = filp->private_data;

	kvm_irqfd_release(kvm);

	kvm_put_kvm(kvm);
	return 0;
}