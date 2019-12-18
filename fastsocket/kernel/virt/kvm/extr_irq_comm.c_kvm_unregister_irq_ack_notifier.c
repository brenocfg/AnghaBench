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
struct kvm_irq_ack_notifier {int /*<<< orphan*/  link; } ;
struct kvm {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void kvm_unregister_irq_ack_notifier(struct kvm *kvm,
				    struct kvm_irq_ack_notifier *kian)
{
	mutex_lock(&kvm->irq_lock);
	hlist_del_init_rcu(&kian->link);
	mutex_unlock(&kvm->irq_lock);
	synchronize_rcu();
}