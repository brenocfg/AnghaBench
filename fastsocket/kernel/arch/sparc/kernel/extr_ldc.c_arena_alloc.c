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
struct iommu_arena {unsigned long limit; unsigned long hint; int /*<<< orphan*/  map; } ;
struct ldc_iommu {struct iommu_arena arena; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ test_bit (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static long arena_alloc(struct ldc_iommu *iommu, unsigned long npages)
{
	struct iommu_arena *arena = &iommu->arena;
	unsigned long n, i, start, end, limit;
	int pass;

	limit = arena->limit;
	start = arena->hint;
	pass = 0;

again:
	n = find_next_zero_bit(arena->map, limit, start);
	end = n + npages;
	if (unlikely(end >= limit)) {
		if (likely(pass < 1)) {
			limit = start;
			start = 0;
			pass++;
			goto again;
		} else {
			/* Scanned the whole thing, give up. */
			return -1;
		}
	}

	for (i = n; i < end; i++) {
		if (test_bit(i, arena->map)) {
			start = i + 1;
			goto again;
		}
	}

	for (i = n; i < end; i++)
		__set_bit(i, arena->map);

	arena->hint = end;

	return n;
}