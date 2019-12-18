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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 size_t PAGE_CACHE_MASK ; 
 size_t PAGE_CACHE_SHIFT ; 
 size_t PAGE_CACHE_SIZE ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

void
_copy_from_pages(char *p, struct page **pages, size_t pgbase, size_t len)
{
	struct page **pgfrom;
	char *vfrom;
	size_t copy;

	pgfrom = pages + (pgbase >> PAGE_CACHE_SHIFT);
	pgbase &= ~PAGE_CACHE_MASK;

	do {
		copy = PAGE_CACHE_SIZE - pgbase;
		if (copy > len)
			copy = len;

		vfrom = kmap_atomic(*pgfrom, KM_USER0);
		memcpy(p, vfrom + pgbase, copy);
		kunmap_atomic(vfrom, KM_USER0);

		pgbase += copy;
		if (pgbase == PAGE_CACHE_SIZE) {
			pgbase = 0;
			pgfrom++;
		}
		p += copy;

	} while ((len -= copy) != 0);
}