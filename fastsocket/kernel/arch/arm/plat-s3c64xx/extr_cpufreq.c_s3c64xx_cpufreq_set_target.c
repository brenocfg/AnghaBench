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
struct s3c64xx_dvfs {int /*<<< orphan*/  vddarm_max; int /*<<< orphan*/  vddarm_min; } ;
struct cpufreq_policy {int dummy; } ;
struct cpufreq_freqs {int old; int new; scalar_t__ flags; scalar_t__ cpu; } ;
struct TYPE_3__ {int frequency; size_t index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
 int /*<<< orphan*/  armclk ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int cpufreq_frequency_table_target (struct cpufreq_policy*,TYPE_1__*,unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int regulator_set_voltage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s3c64xx_dvfs* s3c64xx_dvfs_table ; 
 TYPE_1__* s3c64xx_freq_table ; 
 scalar_t__ vddarm ; 

__attribute__((used)) static int s3c64xx_cpufreq_set_target(struct cpufreq_policy *policy,
				      unsigned int target_freq,
				      unsigned int relation)
{
	int ret;
	unsigned int i;
	struct cpufreq_freqs freqs;
	struct s3c64xx_dvfs *dvfs;

	ret = cpufreq_frequency_table_target(policy, s3c64xx_freq_table,
					     target_freq, relation, &i);
	if (ret != 0)
		return ret;

	freqs.cpu = 0;
	freqs.old = clk_get_rate(armclk) / 1000;
	freqs.new = s3c64xx_freq_table[i].frequency;
	freqs.flags = 0;
	dvfs = &s3c64xx_dvfs_table[s3c64xx_freq_table[i].index];

	if (freqs.old == freqs.new)
		return 0;

	pr_debug("cpufreq: Transition %d-%dkHz\n", freqs.old, freqs.new);

	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

#ifdef CONFIG_REGULATOR
	if (vddarm && freqs.new > freqs.old) {
		ret = regulator_set_voltage(vddarm,
					    dvfs->vddarm_min,
					    dvfs->vddarm_max);
		if (ret != 0) {
			pr_err("cpufreq: Failed to set VDDARM for %dkHz: %d\n",
			       freqs.new, ret);
			goto err;
		}
	}
#endif

	ret = clk_set_rate(armclk, freqs.new * 1000);
	if (ret < 0) {
		pr_err("cpufreq: Failed to set rate %dkHz: %d\n",
		       freqs.new, ret);
		goto err;
	}

#ifdef CONFIG_REGULATOR
	if (vddarm && freqs.new < freqs.old) {
		ret = regulator_set_voltage(vddarm,
					    dvfs->vddarm_min,
					    dvfs->vddarm_max);
		if (ret != 0) {
			pr_err("cpufreq: Failed to set VDDARM for %dkHz: %d\n",
			       freqs.new, ret);
			goto err_clk;
		}
	}
#endif

	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	pr_debug("cpufreq: Set actual frequency %lukHz\n",
		 clk_get_rate(armclk) / 1000);

	return 0;

err_clk:
	if (clk_set_rate(armclk, freqs.old * 1000) < 0)
		pr_err("Failed to restore original clock rate\n");
err:
	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	return ret;
}