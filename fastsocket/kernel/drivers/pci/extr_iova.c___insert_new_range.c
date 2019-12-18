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
struct iova_domain {int /*<<< orphan*/  rbroot; } ;
struct iova {unsigned long pfn_hi; unsigned long pfn_lo; } ;

/* Variables and functions */
 struct iova* alloc_iova_mem () ; 
 int /*<<< orphan*/  iova_insert_rbtree (int /*<<< orphan*/ *,struct iova*) ; 

__attribute__((used)) static struct iova *
__insert_new_range(struct iova_domain *iovad,
	unsigned long pfn_lo, unsigned long pfn_hi)
{
	struct iova *iova;

	iova = alloc_iova_mem();
	if (!iova)
		return iova;

	iova->pfn_hi = pfn_hi;
	iova->pfn_lo = pfn_lo;
	iova_insert_rbtree(&iovad->rbroot, iova);
	return iova;
}