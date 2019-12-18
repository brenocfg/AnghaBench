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
struct pt_regs {int dummy; } ;
struct fadump_crash_info_header {int /*<<< orphan*/  cpu_online_mask; struct pt_regs regs; int /*<<< orphan*/  crashing_cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  fadumphdr_addr; int /*<<< orphan*/  dump_registered; } ;

/* Variables and functions */
 struct fadump_crash_info_header* __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cpu_online_mask ; 
 int /*<<< orphan*/  crash_save_vmcoreinfo () ; 
 int /*<<< orphan*/  crashing_cpu ; 
 TYPE_1__ fw_dump ; 
 int /*<<< orphan*/  ppc_save_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  rtas_os_term (char*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void crash_fadump(struct pt_regs *regs, const char *str)
{
	struct fadump_crash_info_header *fdh = NULL;

	if (!fw_dump.dump_registered || !fw_dump.fadumphdr_addr)
		return;

	fdh = __va(fw_dump.fadumphdr_addr);
	crashing_cpu = smp_processor_id();
	fdh->crashing_cpu = crashing_cpu;
	crash_save_vmcoreinfo();

	if (regs)
		fdh->regs = *regs;
	else
		ppc_save_regs(&fdh->regs);

	fdh->cpu_online_mask = *cpu_online_mask;

	/* Call ibm,os-term rtas call to trigger firmware assisted dump */
	rtas_os_term((char *)str);
}