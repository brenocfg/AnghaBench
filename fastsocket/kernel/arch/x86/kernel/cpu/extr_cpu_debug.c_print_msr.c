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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {struct cpu_private* private; } ;
struct cpu_private {unsigned int cpu; unsigned int reg; scalar_t__ file; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_reg_range ; 
 int /*<<< orphan*/  get_cpu_range (unsigned int,unsigned int*,unsigned int*,int,unsigned int) ; 
 int /*<<< orphan*/  print_cpu_data (struct seq_file*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rdmsr_safe_on_cpu (unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_msr(struct seq_file *seq, unsigned cpu, unsigned flag)
{
	unsigned msr, msr_min, msr_max;
	struct cpu_private *priv;
	u32 low, high;
	int i;

	if (seq) {
		priv = seq->private;
		if (priv->file) {
			if (!rdmsr_safe_on_cpu(priv->cpu, priv->reg,
					       &low, &high))
				print_cpu_data(seq, priv->reg, low, high);
			return;
		}
	}

	for (i = 0; i < ARRAY_SIZE(cpu_reg_range); i++) {
		if (!get_cpu_range(cpu, &msr_min, &msr_max, i, flag))
			continue;

		for (msr = msr_min; msr <= msr_max; msr++) {
			if (rdmsr_safe_on_cpu(cpu, msr, &low, &high))
				continue;
			print_cpu_data(seq, msr, low, high);
		}
	}
}