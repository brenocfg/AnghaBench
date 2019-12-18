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
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun3_get_pte (unsigned long) ; 
 int /*<<< orphan*/  sun3_get_segmap (unsigned long) ; 

void print_pte_vaddr (unsigned long vaddr)
{
	printk (" vaddr=%lx [%02lx]", vaddr, sun3_get_segmap (vaddr));
	print_pte (__pte (sun3_get_pte (vaddr)));
}