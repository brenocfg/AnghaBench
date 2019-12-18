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
typedef  int u64 ;
struct TYPE_5__ {int shadow_efer; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;
struct vcpu_vmx {int msr_offset_efer; TYPE_1__* guest_msrs; TYPE_3__ vcpu; } ;
struct TYPE_4__ {int data; int mask; } ;

/* Variables and functions */
 int EFER_LMA ; 
 int EFER_LME ; 
 int EFER_NX ; 
 int EFER_SCE ; 
 int host_efer ; 

__attribute__((used)) static bool update_transition_efer(struct vcpu_vmx *vmx)
{
	int efer_offset = vmx->msr_offset_efer;
	u64 guest_efer;
	u64 ignore_bits;

	if (efer_offset < 0)
		return false;
	guest_efer = vmx->vcpu.arch.shadow_efer;

	/*
	 * NX is emulated; LMA and LME handled by hardware; SCE meaninless
	 * outside long mode
	 */
	ignore_bits = EFER_NX | EFER_SCE;
#ifdef CONFIG_X86_64
	ignore_bits |= EFER_LMA | EFER_LME;
	/* SCE is meaningful only in long mode on Intel */
	if (guest_efer & EFER_LMA)
		ignore_bits &= ~(u64)EFER_SCE;
#endif
	guest_efer &= ~ignore_bits;
	guest_efer |= host_efer & ignore_bits;
	vmx->guest_msrs[efer_offset].data = guest_efer;
	vmx->guest_msrs[efer_offset].mask = ~ignore_bits;
	return true;
}