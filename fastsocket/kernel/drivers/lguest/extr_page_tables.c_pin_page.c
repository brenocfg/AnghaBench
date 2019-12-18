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
struct lg_cpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  demand_page (struct lg_cpu*,unsigned long,int) ; 
 int /*<<< orphan*/  kill_guest (struct lg_cpu*,char*,unsigned long) ; 
 int /*<<< orphan*/  page_writable (struct lg_cpu*,unsigned long) ; 

void pin_page(struct lg_cpu *cpu, unsigned long vaddr)
{
	if (!page_writable(cpu, vaddr) && !demand_page(cpu, vaddr, 2))
		kill_guest(cpu, "bad stack page %#lx", vaddr);
}