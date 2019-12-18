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
struct TYPE_6__ {int /*<<< orphan*/  exit_external_interrupt; int /*<<< orphan*/  exit_external_request; int /*<<< orphan*/  exit_null; } ;
struct TYPE_5__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_3__ stat; TYPE_2__ arch; } ;
struct TYPE_4__ {int icptcode; } ;

/* Variables and functions */

__attribute__((used)) static int handle_noop(struct kvm_vcpu *vcpu)
{
	switch (vcpu->arch.sie_block->icptcode) {
	case 0x0:
		vcpu->stat.exit_null++;
		break;
	case 0x10:
		vcpu->stat.exit_external_request++;
		break;
	case 0x14:
		vcpu->stat.exit_external_interrupt++;
		break;
	default:
		break; /* nothing */
	}
	return 0;
}