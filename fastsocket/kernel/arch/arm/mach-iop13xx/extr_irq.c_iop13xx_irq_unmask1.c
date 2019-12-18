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
 int read_intctl_1 () ; 
 int /*<<< orphan*/  write_intctl_1 (int) ; 

__attribute__((used)) static void
iop13xx_irq_unmask1(unsigned int irq)
{
	write_intctl_1(read_intctl_1() | (1 << (irq - 32)));
}