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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  elf_gregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_CORE_COPY_REGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 

__attribute__((used)) static inline int elf_core_copy_task_regs(struct task_struct *t,
					  elf_gregset_t* elfregs)
{
	ELF_CORE_COPY_REGS((*elfregs), task_pt_regs(t));
	return 1;
}