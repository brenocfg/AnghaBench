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
struct lpfc_hba {int cfg_sriov_nr_virtfn; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_MAX_VFN_PER_PFN ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
lpfc_sriov_nr_virtfn_init(struct lpfc_hba *phba, int val)
{
	if (val >= 0 && val <= LPFC_MAX_VFN_PER_PFN) {
		phba->cfg_sriov_nr_virtfn = val;
		return 0;
	}

	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"3017 Enabling %d virtual functions is not "
			"allowed.\n", val);
	return -EINVAL;
}