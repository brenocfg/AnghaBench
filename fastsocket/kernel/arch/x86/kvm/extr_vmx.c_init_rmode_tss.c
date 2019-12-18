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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct kvm {int /*<<< orphan*/  srcu; } ;
typedef  int gfn_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int RMODE_TSS_SIZE ; 
 scalar_t__ TSS_BASE_SIZE ; 
 int TSS_IOPB_BASE_OFFSET ; 
 scalar_t__ TSS_REDIRECTION_SIZE ; 
 int kvm_clear_guest_page (struct kvm*,int,int /*<<< orphan*/ ,int) ; 
 int kvm_write_guest_page (struct kvm*,int,scalar_t__*,int,int) ; 
 int rmode_tss_base (struct kvm*) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int init_rmode_tss(struct kvm *kvm)
{
	gfn_t fn;
	u16 data = 0;
	int r, idx, ret = 0;

	idx = srcu_read_lock(&kvm->srcu);
	fn = rmode_tss_base(kvm) >> PAGE_SHIFT;
	r = kvm_clear_guest_page(kvm, fn, 0, PAGE_SIZE);
	if (r < 0)
		goto out;
	data = TSS_BASE_SIZE + TSS_REDIRECTION_SIZE;
	r = kvm_write_guest_page(kvm, fn++, &data,
			TSS_IOPB_BASE_OFFSET, sizeof(u16));
	if (r < 0)
		goto out;
	r = kvm_clear_guest_page(kvm, fn++, 0, PAGE_SIZE);
	if (r < 0)
		goto out;
	r = kvm_clear_guest_page(kvm, fn, 0, PAGE_SIZE);
	if (r < 0)
		goto out;
	data = ~0;
	r = kvm_write_guest_page(kvm, fn, &data,
				 RMODE_TSS_SIZE - 2 * PAGE_SIZE - 1,
				 sizeof(u8));
	if (r < 0)
		goto out;

	ret = 1;
out:
	srcu_read_unlock(&kvm->srcu, idx);
	return ret;
}