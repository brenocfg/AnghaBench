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
typedef  int u32 ;
struct kvm_vmx_segment_field {int /*<<< orphan*/  ar_bytes; int /*<<< orphan*/  selector; int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_segment {int type; int s; int dpl; int present; int avl; int l; int db; int g; int unusable; int /*<<< orphan*/  selector; void* limit; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int AR_UNUSABLE_MASK ; 
 int /*<<< orphan*/  emulate_invalid_guest_state ; 
 struct kvm_vmx_segment_field* kvm_vmx_segment_fields ; 
 int /*<<< orphan*/  vmcs_read16 (int /*<<< orphan*/ ) ; 
 void* vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_get_segment(struct kvm_vcpu *vcpu,
			    struct kvm_segment *var, int seg)
{
	struct kvm_vmx_segment_field *sf = &kvm_vmx_segment_fields[seg];
	u32 ar;

	var->base = vmcs_readl(sf->base);
	var->limit = vmcs_read32(sf->limit);
	var->selector = vmcs_read16(sf->selector);
	ar = vmcs_read32(sf->ar_bytes);
	if ((ar & AR_UNUSABLE_MASK) && !emulate_invalid_guest_state)
		ar = 0;
	var->type = ar & 15;
	var->s = (ar >> 4) & 1;
	var->dpl = (ar >> 5) & 3;
	var->present = (ar >> 7) & 1;
	var->avl = (ar >> 12) & 1;
	var->l = (ar >> 13) & 1;
	var->db = (ar >> 14) & 1;
	var->g = (ar >> 15) & 1;
	var->unusable = (ar >> 16) & 1;
}