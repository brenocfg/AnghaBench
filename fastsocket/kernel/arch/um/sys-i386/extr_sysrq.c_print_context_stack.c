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
struct thread_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ __kernel_text_address (unsigned long) ; 
 int /*<<< orphan*/  print_symbol (char*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ valid_stack_ptr (struct thread_info*,unsigned long*) ; 

__attribute__((used)) static inline unsigned long print_context_stack(struct thread_info *tinfo,
				unsigned long *stack, unsigned long ebp)
{
	unsigned long addr;

#ifdef CONFIG_FRAME_POINTER
	while (valid_stack_ptr(tinfo, (void *)ebp)) {
		addr = *(unsigned long *)(ebp + 4);
		printk("%08lx:  [<%08lx>]", ebp + 4, addr);
		print_symbol(" %s", addr);
		printk("\n");
		ebp = *(unsigned long *)ebp;
	}
#else
	while (valid_stack_ptr(tinfo, stack)) {
		addr = *stack;
		if (__kernel_text_address(addr)) {
			printk("%08lx:  [<%08lx>]", (unsigned long) stack, addr);
			print_symbol(" %s", addr);
			printk("\n");
		}
		stack++;
	}
#endif
	return ebp;
}