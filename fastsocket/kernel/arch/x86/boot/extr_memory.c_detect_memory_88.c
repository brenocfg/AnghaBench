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
struct biosregs {int ah; int eflags; int /*<<< orphan*/  ax; } ;
struct TYPE_3__ {int /*<<< orphan*/  ext_mem_k; } ;
struct TYPE_4__ {TYPE_1__ screen_info; } ;

/* Variables and functions */
 int X86_EFLAGS_CF ; 
 TYPE_2__ boot_params ; 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 

__attribute__((used)) static int detect_memory_88(void)
{
	struct biosregs ireg, oreg;

	initregs(&ireg);
	ireg.ah = 0x88;
	intcall(0x15, &ireg, &oreg);

	boot_params.screen_info.ext_mem_k = oreg.ax;

	return -(oreg.eflags & X86_EFLAGS_CF); /* 0 or -1 */
}