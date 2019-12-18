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
struct linux_binprm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ppl; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA32_STACK_TOP ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ia32_init_pp_list () ; 
 int setup_arg_pages (struct linux_binprm*,int /*<<< orphan*/ ,int) ; 

int
ia32_setup_arg_pages (struct linux_binprm *bprm, int executable_stack)
{
	int ret;

	ret = setup_arg_pages(bprm, IA32_STACK_TOP, executable_stack);
	if (!ret) {
		/*
		 * Can't do it in ia64_elf32_init(). Needs to be done before
		 * calls to elf32_map()
		 */
		current->thread.ppl = ia32_init_pp_list();
	}

	return ret;
}