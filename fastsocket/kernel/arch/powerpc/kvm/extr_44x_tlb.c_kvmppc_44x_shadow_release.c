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
struct kvmppc_vcpu_44x {struct kvmppc_44x_shadow_ref* shadow_refs; } ;
struct kvmppc_44x_shadow_ref {int /*<<< orphan*/ * page; scalar_t__ writeable; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_release_page_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_release_page_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_44x_tlbie (unsigned int) ; 
 int /*<<< orphan*/  trace_kvm_stlb_inval (unsigned int) ; 

__attribute__((used)) static void kvmppc_44x_shadow_release(struct kvmppc_vcpu_44x *vcpu_44x,
                                      unsigned int stlb_index)
{
	struct kvmppc_44x_shadow_ref *ref = &vcpu_44x->shadow_refs[stlb_index];

	if (!ref->page)
		return;

	/* Discard from the TLB. */
	/* Note: we could actually invalidate a host mapping, if the host overwrote
	 * this TLB entry since we inserted a guest mapping. */
	kvmppc_44x_tlbie(stlb_index);

	/* Now release the page. */
	if (ref->writeable)
		kvm_release_page_dirty(ref->page);
	else
		kvm_release_page_clean(ref->page);

	ref->page = NULL;

	/* XXX set tlb_44x_index to stlb_index? */

	trace_kvm_stlb_inval(stlb_index);
}