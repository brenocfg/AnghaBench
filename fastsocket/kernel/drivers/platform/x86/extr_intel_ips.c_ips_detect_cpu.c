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
typedef  int u64 ;
typedef  int u16 ;
struct ips_mcp_limits {int core_power_limit; } ;
struct ips_driver {int turbo_toggle_allowed; TYPE_1__* dev; } ;
struct TYPE_4__ {int x86; int x86_model; int /*<<< orphan*/  x86_model_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA32_MISC_ENABLE ; 
 int IA32_MISC_TURBO_EN ; 
 int /*<<< orphan*/  TURBO_POWER_CURRENT_LIMIT ; 
 int TURBO_TDP_MASK ; 
 TYPE_2__ boot_cpu_data ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 struct ips_mcp_limits ips_lv_limits ; 
 struct ips_mcp_limits ips_sv_limits ; 
 struct ips_mcp_limits ips_ulv_limits ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct ips_mcp_limits *ips_detect_cpu(struct ips_driver *ips)
{
	u64 turbo_power, misc_en;
	struct ips_mcp_limits *limits = NULL;
	u16 tdp;

	if (!(boot_cpu_data.x86 == 6 && boot_cpu_data.x86_model == 37)) {
		dev_info(&ips->dev->dev, "Non-IPS CPU detected.\n");
		goto out;
	}

	rdmsrl(IA32_MISC_ENABLE, misc_en);
	/*
	 * If the turbo enable bit isn't set, we shouldn't try to enable/disable
	 * turbo manually or we'll get an illegal MSR access, even though
	 * turbo will still be available.
	 */
	if (misc_en & IA32_MISC_TURBO_EN)
		ips->turbo_toggle_allowed = true;
	else
		ips->turbo_toggle_allowed = false;

	if (strstr(boot_cpu_data.x86_model_id, "CPU       M"))
		limits = &ips_sv_limits;
	else if (strstr(boot_cpu_data.x86_model_id, "CPU       L"))
		limits = &ips_lv_limits;
	else if (strstr(boot_cpu_data.x86_model_id, "CPU       U"))
		limits = &ips_ulv_limits;
	else {
		dev_info(&ips->dev->dev, "No CPUID match found.\n");
		goto out;
	}

	rdmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_power);
	tdp = turbo_power & TURBO_TDP_MASK;

	/* Sanity check TDP against CPU */
	if (limits->core_power_limit != (tdp / 8) * 1000) {
		dev_info(&ips->dev->dev, "CPU TDP doesn't match expected value (found %d, expected %d)\n",
			 tdp / 8, limits->core_power_limit / 1000);
		limits->core_power_limit = (tdp / 8) * 1000;
	}

out:
	return limits;
}