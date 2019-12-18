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
struct cpumf_ctr_info {int /*<<< orphan*/  act_ctl; int /*<<< orphan*/  enable_ctl; int /*<<< orphan*/  auth_ctl; int /*<<< orphan*/  csvn; int /*<<< orphan*/  cfvn; } ;
typedef  int /*<<< orphan*/  cf_info ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  cpum_cf_avail () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memset (struct cpumf_ctr_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,struct cpumf_ctr_info*,int) ; 
 int /*<<< orphan*/  qctri (struct cpumf_ctr_info*) ; 
 int smp_processor_id () ; 

void perf_event_print_debug(void)
{
	struct cpumf_ctr_info cf_info;
	unsigned long flags;
	int cpu;

	if (!cpum_cf_avail())
		return;

	local_irq_save(flags);

	cpu = smp_processor_id();
	memset(&cf_info, 0, sizeof(cf_info));
	if (!qctri(&cf_info)) {
		pr_info("CPU[%i] CPUM_CF: ver=%u.%u A=%04x E=%04x C=%04x\n",
			cpu, cf_info.cfvn, cf_info.csvn,
			cf_info.auth_ctl, cf_info.enable_ctl, cf_info.act_ctl);
		print_hex_dump_bytes("CPUMF Query: ", DUMP_PREFIX_OFFSET,
				     &cf_info, sizeof(cf_info));
	}

	local_irq_restore(flags);
}