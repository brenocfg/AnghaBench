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
struct linux_binprm {unsigned long p; int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int EFAULT ; 
 int MAX_ARG_PAGES ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ copy_to_user (void*,char*,unsigned long) ; 
 char* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elf_fdpic_transfer_args_to_stack(struct linux_binprm *bprm,
					    unsigned long *_sp)
{
	unsigned long index, stop, sp;
	char *src;
	int ret = 0;

	stop = bprm->p >> PAGE_SHIFT;
	sp = *_sp;

	for (index = MAX_ARG_PAGES - 1; index >= stop; index--) {
		src = kmap(bprm->page[index]);
		sp -= PAGE_SIZE;
		if (copy_to_user((void *) sp, src, PAGE_SIZE) != 0)
			ret = -EFAULT;
		kunmap(bprm->page[index]);
		if (ret < 0)
			goto out;
	}

	*_sp = (*_sp - (MAX_ARG_PAGES * PAGE_SIZE - bprm->p)) & ~15;

out:
	return ret;
}