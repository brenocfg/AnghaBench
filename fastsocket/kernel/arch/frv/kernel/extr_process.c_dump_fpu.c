#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  elf_fpregset_t ;
struct TYPE_5__ {TYPE_1__* user; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  f; } ;

/* Variables and functions */
 TYPE_3__* current ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int dump_fpu(struct pt_regs *regs, elf_fpregset_t *fpregs)
{
	memcpy(fpregs,
	       &current->thread.user->f,
	       sizeof(current->thread.user->f));
	return 1;
}