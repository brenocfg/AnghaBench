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
struct lpfc_hba {int cfg_request_firmware_upgrade; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
lpfc_request_firmware_upgrade_init(struct lpfc_hba *phba, int val)
{
	if (val >= 0 && val <= 1) {
		phba->cfg_request_firmware_upgrade = val;
		return 0;
	}
	return -EINVAL;
}