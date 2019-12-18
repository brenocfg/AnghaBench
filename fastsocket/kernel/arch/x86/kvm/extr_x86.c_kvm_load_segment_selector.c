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
typedef  int /*<<< orphan*/  u16 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_segment {int /*<<< orphan*/  selector; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_get_segment (struct kvm_vcpu*,struct kvm_segment*,int) ; 
 int /*<<< orphan*/  kvm_set_segment (struct kvm_vcpu*,struct kvm_segment*,int) ; 

__attribute__((used)) static void kvm_load_segment_selector(struct kvm_vcpu *vcpu, u16 sel, int seg)
{
	struct kvm_segment kvm_seg;
	kvm_get_segment(vcpu, &kvm_seg, seg);
	kvm_seg.selector = sel;
	kvm_set_segment(vcpu, &kvm_seg, seg);
}