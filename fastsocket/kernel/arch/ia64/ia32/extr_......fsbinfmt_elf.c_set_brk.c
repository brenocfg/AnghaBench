#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {unsigned long start_brk; unsigned long brk; int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 scalar_t__ BAD_ADDR (unsigned long) ; 
 unsigned long ELF_PAGEALIGN (unsigned long) ; 
 TYPE_2__* current ; 
 unsigned long do_brk (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_brk(unsigned long start, unsigned long end)
{
	start = ELF_PAGEALIGN(start);
	end = ELF_PAGEALIGN(end);
	if (end > start) {
		unsigned long addr;
		down_write(&current->mm->mmap_sem);
		addr = do_brk(start, end - start);
		up_write(&current->mm->mmap_sem);
		if (BAD_ADDR(addr))
			return addr;
	}
	current->mm->start_brk = current->mm->brk = end;
	return 0;
}