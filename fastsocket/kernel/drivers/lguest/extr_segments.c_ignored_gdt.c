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
 unsigned int GDT_ENTRY_DOUBLEFAULT_TSS ; 
 unsigned int GDT_ENTRY_LGUEST_CS ; 
 unsigned int GDT_ENTRY_LGUEST_DS ; 
 unsigned int GDT_ENTRY_TSS ; 

__attribute__((used)) static bool ignored_gdt(unsigned int num)
{
	return (num == GDT_ENTRY_TSS
		|| num == GDT_ENTRY_LGUEST_CS
		|| num == GDT_ENTRY_LGUEST_DS
		|| num == GDT_ENTRY_DOUBLEFAULT_TSS);
}