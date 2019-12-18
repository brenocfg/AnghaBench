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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_SLEEP_STATE ; 
 scalar_t__ PMU_KEYLARGO_BASED ; 
 int option_lid_wakeup ; 
 int option_server_mode ; 
 scalar_t__ pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pmu_kind ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int
proc_read_options(char *page, char **start, off_t off,
			int count, int *eof, void *data)
{
	char *p = page;

#if defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
	if (pmu_kind == PMU_KEYLARGO_BASED &&
	    pmac_call_feature(PMAC_FTR_SLEEP_STATE,NULL,0,-1) >= 0)
		p += sprintf(p, "lid_wakeup=%d\n", option_lid_wakeup);
#endif
	if (pmu_kind == PMU_KEYLARGO_BASED)
		p += sprintf(p, "server_mode=%d\n", option_server_mode);

	return p - page;
}