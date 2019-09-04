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
struct TYPE_3__ {int /*<<< orphan*/ * vmxon_region; } ;
typedef  TYPE_1__ vmx_cpu_t ;
struct TYPE_4__ {TYPE_1__ cpu_vmx; } ;

/* Variables and functions */
 TYPE_2__* cpu_datap (unsigned int) ; 
 unsigned int real_ncpus ; 
 int /*<<< orphan*/  vmx_pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmx_free_vmxon_regions(void)
{
	unsigned int i;

	for (i=0; i<real_ncpus; i++) {
		vmx_cpu_t *cpu = &cpu_datap(i)->cpu_vmx;

		vmx_pfree(cpu->vmxon_region);
		cpu->vmxon_region = NULL;
	}
}