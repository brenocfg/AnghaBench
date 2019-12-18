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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_ARBPRI ; 
 int /*<<< orphan*/  APIC_DFR ; 
 int /*<<< orphan*/  APIC_ECTRL ; 
 int /*<<< orphan*/  APIC_EFEAT ; 
 int /*<<< orphan*/  APIC_EILVTn (unsigned int) ; 
 int /*<<< orphan*/  APIC_ESR ; 
 int /*<<< orphan*/  APIC_ICR ; 
 int /*<<< orphan*/  APIC_ICR2 ; 
 int /*<<< orphan*/  APIC_ID ; 
 int /*<<< orphan*/  APIC_ISR ; 
 int /*<<< orphan*/  APIC_LDR ; 
 int /*<<< orphan*/  APIC_LVR ; 
 int /*<<< orphan*/  APIC_LVT0 ; 
 int /*<<< orphan*/  APIC_LVT1 ; 
 int /*<<< orphan*/  APIC_LVTERR ; 
 int /*<<< orphan*/  APIC_LVTPC ; 
 int /*<<< orphan*/  APIC_LVTT ; 
 int /*<<< orphan*/  APIC_LVTTHMR ; 
 int /*<<< orphan*/  APIC_PROCPRI ; 
 int /*<<< orphan*/  APIC_SPIV ; 
 int /*<<< orphan*/  APIC_TASKPRI ; 
 int /*<<< orphan*/  APIC_TDCR ; 
 int /*<<< orphan*/  APIC_TMCCT ; 
 int /*<<< orphan*/  APIC_TMICT ; 
 int /*<<< orphan*/  X86_FEATURE_EXTAPIC ; 
 int apic_read (int /*<<< orphan*/ ) ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void print_apic(void *arg)
{
	struct seq_file *seq = arg;

#ifdef CONFIG_X86_LOCAL_APIC
	seq_printf(seq, " LAPIC\t:\n");
	seq_printf(seq, " ID\t\t: %08x\n",  apic_read(APIC_ID) >> 24);
	seq_printf(seq, " LVR\t\t: %08x\n",  apic_read(APIC_LVR));
	seq_printf(seq, " TASKPRI\t: %08x\n",  apic_read(APIC_TASKPRI));
	seq_printf(seq, " ARBPRI\t\t: %08x\n",  apic_read(APIC_ARBPRI));
	seq_printf(seq, " PROCPRI\t: %08x\n",  apic_read(APIC_PROCPRI));
	seq_printf(seq, " LDR\t\t: %08x\n",  apic_read(APIC_LDR));
	seq_printf(seq, " DFR\t\t: %08x\n",  apic_read(APIC_DFR));
	seq_printf(seq, " SPIV\t\t: %08x\n",  apic_read(APIC_SPIV));
	seq_printf(seq, " ISR\t\t: %08x\n",  apic_read(APIC_ISR));
	seq_printf(seq, " ESR\t\t: %08x\n",  apic_read(APIC_ESR));
	seq_printf(seq, " ICR\t\t: %08x\n",  apic_read(APIC_ICR));
	seq_printf(seq, " ICR2\t\t: %08x\n",  apic_read(APIC_ICR2));
	seq_printf(seq, " LVTT\t\t: %08x\n",  apic_read(APIC_LVTT));
	seq_printf(seq, " LVTTHMR\t: %08x\n",  apic_read(APIC_LVTTHMR));
	seq_printf(seq, " LVTPC\t\t: %08x\n",  apic_read(APIC_LVTPC));
	seq_printf(seq, " LVT0\t\t: %08x\n",  apic_read(APIC_LVT0));
	seq_printf(seq, " LVT1\t\t: %08x\n",  apic_read(APIC_LVT1));
	seq_printf(seq, " LVTERR\t\t: %08x\n",  apic_read(APIC_LVTERR));
	seq_printf(seq, " TMICT\t\t: %08x\n",  apic_read(APIC_TMICT));
	seq_printf(seq, " TMCCT\t\t: %08x\n",  apic_read(APIC_TMCCT));
	seq_printf(seq, " TDCR\t\t: %08x\n",  apic_read(APIC_TDCR));
	if (boot_cpu_has(X86_FEATURE_EXTAPIC)) {
		unsigned int i, v, maxeilvt;

		v = apic_read(APIC_EFEAT);
		maxeilvt = (v >> 16) & 0xff;
		seq_printf(seq, " EFEAT\t\t: %08x\n", v);
		seq_printf(seq, " ECTRL\t\t: %08x\n", apic_read(APIC_ECTRL));

		for (i = 0; i < maxeilvt; i++) {
			v = apic_read(APIC_EILVTn(i));
			seq_printf(seq, " EILVT%d\t\t: %08x\n", i, v);
		}
	}
#endif /* CONFIG_X86_LOCAL_APIC */
	seq_printf(seq, "\n MSR\t:\n");
}