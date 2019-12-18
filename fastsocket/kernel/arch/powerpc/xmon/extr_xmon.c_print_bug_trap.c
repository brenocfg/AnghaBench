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
struct pt_regs {int msr; unsigned long nip; } ;
struct bug_entry {char* file; int line; scalar_t__ bug_addr; } ;

/* Variables and functions */
 int MSR_PR ; 
 unsigned long PAGE_OFFSET ; 
 struct bug_entry* find_bug (unsigned long) ; 
 scalar_t__ is_warning_bug (struct bug_entry const*) ; 
 int /*<<< orphan*/  printf (char*,void*,...) ; 

__attribute__((used)) static void print_bug_trap(struct pt_regs *regs)
{
#ifdef CONFIG_BUG
	const struct bug_entry *bug;
	unsigned long addr;

	if (regs->msr & MSR_PR)
		return;		/* not in kernel */
	addr = regs->nip;	/* address of trap instruction */
	if (addr < PAGE_OFFSET)
		return;
	bug = find_bug(regs->nip);
	if (bug == NULL)
		return;
	if (is_warning_bug(bug))
		return;

#ifdef CONFIG_DEBUG_BUGVERBOSE
	printf("kernel BUG at %s:%u!\n",
	       bug->file, bug->line);
#else
	printf("kernel BUG at %p!\n", (void *)bug->bug_addr);
#endif
#endif /* CONFIG_BUG */
}