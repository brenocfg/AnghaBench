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
union ia64_rr {unsigned long ps; int /*<<< orphan*/  val; } ;
typedef  unsigned long u64 ;
struct thash_data {unsigned long etag; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 unsigned long INVALID_TI_TAG ; 
 unsigned long PSIZE (unsigned long) ; 
 int /*<<< orphan*/  ia64_get_rr (unsigned long) ; 
 scalar_t__ ia64_thash (unsigned long) ; 
 unsigned long ia64_ttag (unsigned long) ; 
 int /*<<< orphan*/  machine_tlb_purge (unsigned long,unsigned long) ; 

__attribute__((used)) static void vhpt_purge(struct kvm_vcpu *v, u64 va, u64 ps)
{
	struct thash_data *cur;
	u64 start, size, tag, num;
	union ia64_rr rr;

	start = va & ~((1UL << ps) - 1);
	rr.val = ia64_get_rr(va);
	size = PSIZE(rr.ps);
	num = 1UL << ((ps < rr.ps) ? 0 : (ps - rr.ps));
	while (num) {
		cur = (struct thash_data *)ia64_thash(start);
		tag = ia64_ttag(start);
		if (cur->etag == tag)
			cur->etag = INVALID_TI_TAG;
		start += size;
		num--;
	}
	machine_tlb_purge(va, ps);
}