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
struct lpfc_hba {int cfg_aer_support; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
lpfc_aer_support_init(struct lpfc_hba *phba, int val)
{
	if (val == 0 || val == 1) {
		phba->cfg_aer_support = val;
		return 0;
	}
	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2712 lpfc_aer_support attribute value %d out "
			"of range, allowed values are 0|1, setting it "
			"to default value of 1\n", val);
	/* By default, try to enable AER on a device */
	phba->cfg_aer_support = 1;
	return -EINVAL;
}