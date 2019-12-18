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

/* Variables and functions */
 int HUGETLB_PAGESIZE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,void*,size_t,int /*<<< orphan*/ ) ; 
 int munmap (void*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

void plat_munmap(void *ptr, size_t size)
{
	int ret;

	ret = munmap(ptr, size);
	if (ret != 0 && (size & (HUGETLB_PAGESIZE - 1))) {
		// prehaps an autorounded hugetlb mapping?
		size = (size + HUGETLB_PAGESIZE - 1) & ~(HUGETLB_PAGESIZE - 1);
		ret = munmap(ptr, size);
	}
	if (ret != 0) {
		fprintf(stderr,
			"munmap(%p, %zu) failed: %d\n", ptr, size, errno);
	}
}