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
struct linux_binprm {unsigned long p; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  KM_USER0 ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  free_arg_page (struct linux_binprm*,int) ; 
 struct page* get_arg_page (struct linux_binprm*,unsigned long,int /*<<< orphan*/ ) ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_arg_page (struct page*) ; 

int remove_arg_zero(struct linux_binprm *bprm)
{
	int ret = 0;
	unsigned long offset;
	char *kaddr;
	struct page *page;

	if (!bprm->argc)
		return 0;

	do {
		offset = bprm->p & ~PAGE_MASK;
		page = get_arg_page(bprm, bprm->p, 0);
		if (!page) {
			ret = -EFAULT;
			goto out;
		}
		kaddr = kmap_atomic(page, KM_USER0);

		for (; offset < PAGE_SIZE && kaddr[offset];
				offset++, bprm->p++)
			;

		kunmap_atomic(kaddr, KM_USER0);
		put_arg_page(page);

		if (offset == PAGE_SIZE)
			free_arg_page(bprm, (bprm->p >> PAGE_SHIFT) - 1);
	} while (offset == PAGE_SIZE);

	bprm->p++;
	bprm->argc--;
	ret = 0;

out:
	return ret;
}