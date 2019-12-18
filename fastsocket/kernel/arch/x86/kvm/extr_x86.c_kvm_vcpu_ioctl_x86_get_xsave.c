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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvm_xsave {int /*<<< orphan*/ * region; } ;
struct TYPE_4__ {TYPE_2__* state; } ;
struct TYPE_6__ {TYPE_1__ guest_fpu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct i387_fxsave_struct {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  fxsave; int /*<<< orphan*/  xsave; } ;

/* Variables and functions */
 int XSAVE_HDR_OFFSET ; 
 int /*<<< orphan*/  XSTATE_FPSSE ; 
 scalar_t__ cpu_has_xsave ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int xstate_size ; 

__attribute__((used)) static void kvm_vcpu_ioctl_x86_get_xsave(struct kvm_vcpu *vcpu,
					 struct kvm_xsave *guest_xsave)
{
	if (cpu_has_xsave)
		memcpy(guest_xsave->region,
			&vcpu->arch.guest_fpu.state->xsave,
			xstate_size);
	else {
		memcpy(guest_xsave->region,
			&vcpu->arch.guest_fpu.state->fxsave,
			sizeof(struct i387_fxsave_struct));
		*(u64 *)&guest_xsave->region[XSAVE_HDR_OFFSET / sizeof(u32)] =
			XSTATE_FPSSE;
	}
}