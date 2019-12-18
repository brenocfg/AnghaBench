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
struct lpfc_hba {scalar_t__ sli_rev; int cfg_fcp_cpu_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_DRIVER_CPU_MAP ; 
 int LPFC_MAX_CPU_MAP ; 
 int LPFC_MIN_CPU_MAP ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
lpfc_fcp_cpu_map_init(struct lpfc_hba *phba, int val)
{
	if (phba->sli_rev != LPFC_SLI_REV4) {
		phba->cfg_fcp_cpu_map = 0;
		return 0;
	}

	if (val >= LPFC_MIN_CPU_MAP && val <= LPFC_MAX_CPU_MAP) {
		phba->cfg_fcp_cpu_map = val;
		return 0;
	}

	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"3326 fcp_cpu_map: %d out of range, using default\n",
			val);
	phba->cfg_fcp_cpu_map = LPFC_DRIVER_CPU_MAP;

	return 0;
}