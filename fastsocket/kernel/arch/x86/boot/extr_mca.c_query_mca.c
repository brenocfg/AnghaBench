#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct biosregs {int ah; int eflags; int /*<<< orphan*/  bx; int /*<<< orphan*/  es; } ;
struct TYPE_2__ {int /*<<< orphan*/  sys_desc_table; } ;

/* Variables and functions */
 int X86_EFLAGS_CF ; 
 TYPE_1__ boot_params ; 
 int /*<<< orphan*/  copy_from_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 
 int rdfs16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 

int query_mca(void)
{
	struct biosregs ireg, oreg;
	u16 len;

	initregs(&ireg);
	ireg.ah = 0xc0;
	intcall(0x15, &ireg, &oreg);

	if (oreg.eflags & X86_EFLAGS_CF)
		return -1;	/* No MCA present */

	set_fs(oreg.es);
	len = rdfs16(oreg.bx);

	if (len > sizeof(boot_params.sys_desc_table))
		len = sizeof(boot_params.sys_desc_table);

	copy_from_fs(&boot_params.sys_desc_table, oreg.bx, len);
	return 0;
}