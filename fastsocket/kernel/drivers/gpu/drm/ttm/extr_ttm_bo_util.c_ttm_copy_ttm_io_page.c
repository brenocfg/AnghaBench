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
 int /*<<< orphan*/  memcpy_toio (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 
 void* vmap (struct page**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

__attribute__((used)) static int ttm_copy_ttm_io_page(struct ttm_tt *ttm, void *dst,
				unsigned long page,
				pgprot_t prot)
{
	struct page *s = ttm->pages[page];
	void *src;

	if (!s)
		return -ENOMEM;

	dst = (void *)((unsigned long)dst + (page << PAGE_SHIFT));
#ifdef CONFIG_X86
	src = kmap_atomic_prot(s, KM_USER0, prot);
#else
	if (pgprot_val(prot) != pgprot_val(PAGE_KERNEL))
		src = vmap(&s, 1, 0, prot);
	else
		src = kmap(s);
#endif
	if (!src)
		return -ENOMEM;

	memcpy_toio(dst, src, PAGE_SIZE);

#ifdef CONFIG_X86
	kunmap_atomic(src, KM_USER0);
#else
	if (pgprot_val(prot) != pgprot_val(PAGE_KERNEL))
		vunmap(src);
	else
		kunmap(s);
#endif

	return 0;
}