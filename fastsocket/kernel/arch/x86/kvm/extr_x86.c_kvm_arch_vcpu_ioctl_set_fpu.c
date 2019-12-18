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
struct TYPE_5__ {TYPE_1__* state; } ;
struct TYPE_6__ {TYPE_2__ guest_fpu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct kvm_fpu {int /*<<< orphan*/  xmm; int /*<<< orphan*/  last_dp; int /*<<< orphan*/  last_ip; int /*<<< orphan*/  last_opcode; int /*<<< orphan*/  ftwx; int /*<<< orphan*/  fsw; int /*<<< orphan*/  fcw; int /*<<< orphan*/  fpr; } ;
struct i387_fxsave_struct {int /*<<< orphan*/  xmm_space; int /*<<< orphan*/  rdp; int /*<<< orphan*/  rip; int /*<<< orphan*/  fop; int /*<<< orphan*/  twd; int /*<<< orphan*/  swd; int /*<<< orphan*/  cwd; int /*<<< orphan*/  st_space; } ;
struct TYPE_4__ {struct i387_fxsave_struct fxsave; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_set_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
{
	struct i387_fxsave_struct *fxsave =
			&vcpu->arch.guest_fpu.state->fxsave;

	vcpu_load(vcpu);

	memcpy(fxsave->st_space, fpu->fpr, 128);
	fxsave->cwd = fpu->fcw;
	fxsave->swd = fpu->fsw;
	fxsave->twd = fpu->ftwx;
	fxsave->fop = fpu->last_opcode;
	fxsave->rip = fpu->last_ip;
	fxsave->rdp = fpu->last_dp;
	memcpy(fxsave->xmm_space, fpu->xmm, sizeof fxsave->xmm_space);

	vcpu_put(vcpu);

	return 0;
}