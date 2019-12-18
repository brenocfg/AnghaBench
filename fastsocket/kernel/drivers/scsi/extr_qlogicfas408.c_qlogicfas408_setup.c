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

/* Variables and functions */
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  REG1 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int qlcfg5 ; 
 int qlcfg8 ; 
 int qlcfg9 ; 

void qlogicfas408_setup(int qbase, int id, int int_type)
{
	outb(1, qbase + 8);	/* set for PIO pseudo DMA */
	REG0;
	outb(0x40 | qlcfg8 | id, qbase + 8);	/* (ini) bus id, disable scsi rst */
	outb(qlcfg5, qbase + 5);	/* select timer */
	outb(qlcfg9, qbase + 9);	/* prescaler */

#if QL_RESET_AT_START
	outb(3, qbase + 3);

	REG1;
	/* FIXME: timeout */
	while (inb(qbase + 0xf) & 4)
		cpu_relax();

	REG0;
#endif
}