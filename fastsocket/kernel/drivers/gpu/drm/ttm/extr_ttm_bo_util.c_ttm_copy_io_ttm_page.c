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
struct ttm_tt {struct page** pages; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* kmap (struct page*) ; 
 void* kmap_atomic_prot (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 
 void* vmap (struct page**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

__attribute__((used)) static int ttm_copy_io_ttm_page(struct ttm_tt *ttm, void *src,
				unsigned long page,
				pgprot_t prot)
{
	struct page *d = ttm->pages[page];
	void *dst;

	if (!d)
		return -ENOMEM;

	src = (void *)((unsigned long)src + (page << PAGE_SHIFT));

#ifdef CONFIG_X86
	dst = kmap_atomic_prot(d, KM_USER0, prot);
#else
	if (pgprot_val(prot) != pgprot_val(PAGE_KERNEL))
		dst = vmap(&d, 1, 0, prot);
	else
		dst = kmap(d);
#endif
	if (!dst)
		return -ENOMEM;

	memcpy_fromio(dst, src, PAGE_SIZE);

#ifdef CONFIG_X86
	kunmap_atomic(dst, KM_USER0);
#else
	if (pgprot_val(prot) != pgprot_val(PAGE_KERNEL))
		vunmap(dst);
	else
		kunmap(d);
#endif

	return 0;
}