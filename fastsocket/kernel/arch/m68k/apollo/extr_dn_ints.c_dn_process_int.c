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

/* Variables and functions */
 int /*<<< orphan*/  __m68k_handle_int (unsigned int,struct pt_regs*) ; 
 scalar_t__ pica ; 
 scalar_t__ picb ; 

void dn_process_int(unsigned int irq, struct pt_regs *fp)
{
	__m68k_handle_int(irq, fp);

	*(volatile unsigned char *)(pica)=0x20;
	*(volatile unsigned char *)(picb)=0x20;
}