#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  maddr; } ;
typedef  TYPE_1__ xmaddr_t ;
struct thread_struct {int /*<<< orphan*/ * tls_array; } ;
struct multicall_space {int /*<<< orphan*/  mc; } ;
struct desc_struct {int dummy; } ;

/* Variables and functions */
 unsigned int GDT_ENTRY_TLS_MIN ; 
 int /*<<< orphan*/  MULTI_update_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct multicall_space __xen_mc_entry (int /*<<< orphan*/ ) ; 
 TYPE_1__ arbitrary_virt_to_machine (struct desc_struct*) ; 
 struct desc_struct* get_cpu_gdt_table (unsigned int) ; 

__attribute__((used)) static void load_TLS_descriptor(struct thread_struct *t,
				unsigned int cpu, unsigned int i)
{
	struct desc_struct *gdt = get_cpu_gdt_table(cpu);
	xmaddr_t maddr = arbitrary_virt_to_machine(&gdt[GDT_ENTRY_TLS_MIN+i]);
	struct multicall_space mc = __xen_mc_entry(0);

	MULTI_update_descriptor(mc.mc, maddr.maddr, t->tls_array[i]);
}