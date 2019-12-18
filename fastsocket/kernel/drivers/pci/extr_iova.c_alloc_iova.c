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
struct iova_domain {int dummy; } ;
struct iova {int dummy; } ;

/* Variables and functions */
 int __alloc_and_insert_iova_range (struct iova_domain*,unsigned long,unsigned long,struct iova*,int) ; 
 unsigned long __roundup_pow_of_two (unsigned long) ; 
 struct iova* alloc_iova_mem () ; 
 int /*<<< orphan*/  free_iova_mem (struct iova*) ; 

struct iova *
alloc_iova(struct iova_domain *iovad, unsigned long size,
	unsigned long limit_pfn,
	bool size_aligned)
{
	struct iova *new_iova;
	int ret;

	new_iova = alloc_iova_mem();
	if (!new_iova)
		return NULL;

	/* If size aligned is set then round the size to
	 * to next power of two.
	 */
	if (size_aligned)
		size = __roundup_pow_of_two(size);

	ret = __alloc_and_insert_iova_range(iovad, size, limit_pfn,
			new_iova, size_aligned);

	if (ret) {
		free_iova_mem(new_iova);
		return NULL;
	}

	return new_iova;
}