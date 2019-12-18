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
typedef  int u32 ;
struct ips_driver {int cpu_turbo_enabled; int gpu_turbo_enabled; void* mcp_power_limit; void* mcp_temp_limit; void* mch_power_limit; void* core_power_limit; scalar_t__ gpu_busy; } ;

/* Variables and functions */
 int HTS_GTD_DIS ; 
 int HTS_PCTD_DIS ; 
 int /*<<< orphan*/  THM_HTS ; 
 int /*<<< orphan*/  THM_MMGPC ; 
 int /*<<< orphan*/  THM_MPCPC ; 
 int /*<<< orphan*/  THM_MPPC ; 
 int /*<<< orphan*/  THM_PTL ; 
 int thm_readl (int /*<<< orphan*/ ) ; 
 void* thm_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_limits (struct ips_driver*) ; 

__attribute__((used)) static void update_turbo_limits(struct ips_driver *ips)
{
	u32 hts = thm_readl(THM_HTS);

	ips->cpu_turbo_enabled = !(hts & HTS_PCTD_DIS);
	/* 
	 * Disable turbo for now, until we can figure out why the power figures
	 * are wrong
	 */
	ips->cpu_turbo_enabled = false;

	if (ips->gpu_busy)
		ips->gpu_turbo_enabled = !(hts & HTS_GTD_DIS);

	ips->core_power_limit = thm_readw(THM_MPCPC);
	ips->mch_power_limit = thm_readw(THM_MMGPC);
	ips->mcp_temp_limit = thm_readw(THM_PTL);
	ips->mcp_power_limit = thm_readw(THM_MPPC);

	verify_limits(ips);
	/* Ignore BIOS CPU vs GPU pref */
}