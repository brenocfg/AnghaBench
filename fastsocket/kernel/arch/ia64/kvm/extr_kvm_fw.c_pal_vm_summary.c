#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct ia64_pal_retval {int /*<<< orphan*/  v1; int /*<<< orphan*/  v0; int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  rid_size; int /*<<< orphan*/  impl_va_msb; } ;
struct TYPE_7__ {int /*<<< orphan*/  pvi2_val; TYPE_1__ pal_vm_info_2_s; } ;
typedef  TYPE_3__ pal_vm_info_2_u_t ;
struct TYPE_6__ {int max_itr_entry; int max_dtr_entry; } ;
struct TYPE_8__ {int /*<<< orphan*/  pvi1_val; TYPE_2__ pal_vm_info_1_s; } ;
typedef  TYPE_4__ pal_vm_info_1_u_t ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_IMPL_VA_MSB ; 
 int /*<<< orphan*/  GUEST_RID_BITS ; 
 int /*<<< orphan*/  PAL_CALL (struct ia64_pal_retval,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAL_VM_SUMMARY ; 

__attribute__((used)) static struct ia64_pal_retval pal_vm_summary(struct kvm_vcpu *vcpu)
{

	pal_vm_info_1_u_t vminfo1;
	pal_vm_info_2_u_t vminfo2;
	struct ia64_pal_retval result;

	PAL_CALL(result, PAL_VM_SUMMARY, 0, 0, 0);
	if (!result.status) {
		vminfo1.pvi1_val = result.v0;
		vminfo1.pal_vm_info_1_s.max_itr_entry = 8;
		vminfo1.pal_vm_info_1_s.max_dtr_entry = 8;
		result.v0 = vminfo1.pvi1_val;
		vminfo2.pal_vm_info_2_s.impl_va_msb = GUEST_IMPL_VA_MSB;
		vminfo2.pal_vm_info_2_s.rid_size = GUEST_RID_BITS;
		result.v1 = vminfo2.pvi2_val;
	}

	return result;
}