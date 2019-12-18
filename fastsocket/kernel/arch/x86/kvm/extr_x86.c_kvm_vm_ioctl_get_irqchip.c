#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvm_pic_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioapic; int /*<<< orphan*/  pic; } ;
struct kvm_irqchip {int chip_id; TYPE_1__ chip; } ;
struct kvm {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pics; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_IRQCHIP_IOAPIC 130 
#define  KVM_IRQCHIP_PIC_MASTER 129 
#define  KVM_IRQCHIP_PIC_SLAVE 128 
 int kvm_get_ioapic (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* pic_irqchip (struct kvm*) ; 

__attribute__((used)) static int kvm_vm_ioctl_get_irqchip(struct kvm *kvm, struct kvm_irqchip *chip)
{
	int r;

	r = 0;
	switch (chip->chip_id) {
	case KVM_IRQCHIP_PIC_MASTER:
		memcpy(&chip->chip.pic,
			&pic_irqchip(kvm)->pics[0],
			sizeof(struct kvm_pic_state));
		break;
	case KVM_IRQCHIP_PIC_SLAVE:
		memcpy(&chip->chip.pic,
			&pic_irqchip(kvm)->pics[1],
			sizeof(struct kvm_pic_state));
		break;
	case KVM_IRQCHIP_IOAPIC:
		r = kvm_get_ioapic(kvm, &chip->chip.ioapic);
		break;
	default:
		r = -EINVAL;
		break;
	}
	return r;
}