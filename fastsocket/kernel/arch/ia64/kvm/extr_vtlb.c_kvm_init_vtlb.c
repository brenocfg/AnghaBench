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
struct TYPE_4__ {int /*<<< orphan*/  num; } ;
struct TYPE_3__ {TYPE_2__ vtlb; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTLB_NUM_ENTRIES ; 
 int /*<<< orphan*/  VTLB_SHIFT ; 
 int /*<<< orphan*/  thash_init (TYPE_2__*,int /*<<< orphan*/ ) ; 

void kvm_init_vtlb(struct kvm_vcpu *v)
{
	v->arch.vtlb.num = VTLB_NUM_ENTRIES;
	thash_init(&v->arch.vtlb, VTLB_SHIFT);
}