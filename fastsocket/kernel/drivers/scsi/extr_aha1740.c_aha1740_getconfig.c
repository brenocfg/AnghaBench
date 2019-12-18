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
 int /*<<< orphan*/  INTDEF (unsigned int) ; 
 int /*<<< orphan*/  RESV1 (unsigned int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aha1740_getconfig(unsigned int base, unsigned int *irq_level,
			      unsigned int *irq_type,
			      unsigned int *translation)
{
	static int intab[] = { 9, 10, 11, 12, 0, 14, 15, 0 };

	*irq_level = intab[inb(INTDEF(base)) & 0x7];
	*irq_type  = (inb(INTDEF(base)) & 0x8) >> 3;
	*translation = inb(RESV1(base)) & 0x1;
	outb(inb(INTDEF(base)) | 0x10, INTDEF(base));
}