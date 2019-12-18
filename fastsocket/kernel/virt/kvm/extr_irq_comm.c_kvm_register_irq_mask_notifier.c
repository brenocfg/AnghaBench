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
struct kvm_irq_mask_notifier {int irq; int /*<<< orphan*/  link; } ;
struct kvm {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  mask_notifier_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kvm_register_irq_mask_notifier(struct kvm *kvm, int irq,
				    struct kvm_irq_mask_notifier *kimn)
{
	mutex_lock(&kvm->irq_lock);
	kimn->irq = irq;
	hlist_add_head_rcu(&kimn->link, &kvm->mask_notifier_list);
	mutex_unlock(&kvm->irq_lock);
}