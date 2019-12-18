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
struct lg_cpu {TYPE_1__* lg; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {scalar_t__ pfn_limit; } ;

/* Variables and functions */
 int _PAGE_PSE ; 
 int /*<<< orphan*/  kill_guest (struct lg_cpu*,char*) ; 
 int pte_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_gpte(struct lg_cpu *cpu, pte_t gpte)
{
	if ((pte_flags(gpte) & _PAGE_PSE) ||
	    pte_pfn(gpte) >= cpu->lg->pfn_limit)
		kill_guest(cpu, "bad page table entry");
}