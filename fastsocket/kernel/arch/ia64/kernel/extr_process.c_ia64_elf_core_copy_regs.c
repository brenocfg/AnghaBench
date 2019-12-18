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
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  elf_gregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_copy_regs ; 
 int /*<<< orphan*/  unw_init_running (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ia64_elf_core_copy_regs (struct pt_regs *pt, elf_gregset_t dst)
{
	unw_init_running(do_copy_regs, dst);
}