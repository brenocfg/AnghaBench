#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lg_cpu {size_t cpu_pgd; TYPE_2__* lg; } ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_4__ {TYPE_1__* pgdirs; } ;
struct TYPE_3__ {unsigned long gpgdir; } ;

/* Variables and functions */
 unsigned long PGDIR_SHIFT ; 

__attribute__((used)) static unsigned long gpgd_addr(struct lg_cpu *cpu, unsigned long vaddr)
{
	unsigned int index = vaddr >> (PGDIR_SHIFT);
	return cpu->lg->pgdirs[cpu->cpu_pgd].gpgdir + index * sizeof(pgd_t);
}