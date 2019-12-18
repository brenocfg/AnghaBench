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
struct lg_cpu {int /*<<< orphan*/  cpu_pgd; int /*<<< orphan*/  lg; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_user_mappings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void guest_pagetable_flush_user(struct lg_cpu *cpu)
{
	/* Drop the userspace part of the current page table. */
	flush_user_mappings(cpu->lg, cpu->cpu_pgd);
}