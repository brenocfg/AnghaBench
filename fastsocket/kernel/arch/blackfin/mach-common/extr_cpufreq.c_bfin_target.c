#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {int dummy; } ;
struct cpufreq_freqs {unsigned long new; int /*<<< orphan*/  old; scalar_t__ cpu; } ;
typedef  int cycles_t ;
struct TYPE_5__ {unsigned long frequency; } ;
struct TYPE_4__ {unsigned int csel; unsigned int tscale; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
 int EINVAL ; 
 unsigned int SSEL ; 
 int /*<<< orphan*/  SSYNC () ; 
 int __bfin_cycles_mod ; 
 int /*<<< orphan*/  __bfin_cycles_off ; 
 TYPE_2__* bfin_freq_table ; 
 int /*<<< orphan*/  bfin_getfreq_khz (int /*<<< orphan*/ ) ; 
 unsigned int bfin_read_PLL_DIV () ; 
 int /*<<< orphan*/  bfin_write_PLL_DIV (unsigned int) ; 
 int /*<<< orphan*/  bfin_write_TSCALE (unsigned int) ; 
 scalar_t__ cpufreq_frequency_table_target (struct cpufreq_policy*,TYPE_2__*,unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 TYPE_1__* dpm_state_table ; 
 int get_cycles () ; 
 int /*<<< orphan*/  local_irq_restore_hw (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save_hw (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int bfin_target(struct cpufreq_policy *policy,
			unsigned int target_freq, unsigned int relation)
{
	unsigned int index, plldiv, tscale;
	unsigned long flags, cclk_hz;
	struct cpufreq_freqs freqs;
	cycles_t cycles;

	if (cpufreq_frequency_table_target(policy, bfin_freq_table,
		 target_freq, relation, &index))
		return -EINVAL;

	cclk_hz = bfin_freq_table[index].frequency;

	freqs.old = bfin_getfreq_khz(0);
	freqs.new = cclk_hz;
	freqs.cpu = 0;

	pr_debug("cpufreq: changing cclk to %lu; target = %u, oldfreq = %u\n",
		 cclk_hz, target_freq, freqs.old);

	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);
	local_irq_save_hw(flags);
		plldiv = (bfin_read_PLL_DIV() & SSEL) | dpm_state_table[index].csel;
		tscale = dpm_state_table[index].tscale;
		bfin_write_PLL_DIV(plldiv);
		/* we have to adjust the core timer, because it is using cclk */
		bfin_write_TSCALE(tscale);
		cycles = get_cycles();
		SSYNC();
	cycles += 10; /* ~10 cycles we lose after get_cycles() */
	__bfin_cycles_off += (cycles << __bfin_cycles_mod) - (cycles << index);
	__bfin_cycles_mod = index;
	local_irq_restore_hw(flags);
	/* TODO: just test case for cycles clock source, remove later */
	pr_debug("cpufreq: done\n");
	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	return 0;
}