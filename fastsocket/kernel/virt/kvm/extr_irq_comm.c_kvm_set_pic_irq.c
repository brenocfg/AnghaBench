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
struct kvm_pic {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ irqchip; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int kvm_pic_set_irq (struct kvm_pic*,int /*<<< orphan*/ ,int,int) ; 
 struct kvm_pic* pic_irqchip (struct kvm*) ; 

__attribute__((used)) static int kvm_set_pic_irq(struct kvm_kernel_irq_routing_entry *e,
			   struct kvm *kvm, int irq_source_id, int level)
{
#ifdef CONFIG_X86
	struct kvm_pic *pic = pic_irqchip(kvm);
	return kvm_pic_set_irq(pic, e->irqchip.pin, irq_source_id, level);
#else
	return -1;
#endif
}