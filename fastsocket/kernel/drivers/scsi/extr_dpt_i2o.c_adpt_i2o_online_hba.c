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
typedef  int /*<<< orphan*/  adpt_hba ;

/* Variables and functions */
 int /*<<< orphan*/  adpt_i2o_delete_hba (int /*<<< orphan*/ *) ; 
 scalar_t__ adpt_i2o_enable_hba (int /*<<< orphan*/ *) ; 
 scalar_t__ adpt_i2o_systab_send (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adpt_i2o_online_hba(adpt_hba* pHba)
{
	if (adpt_i2o_systab_send(pHba) < 0) {
		adpt_i2o_delete_hba(pHba);
		return -1;
	}
	/* In READY state */

	if (adpt_i2o_enable_hba(pHba) < 0) {
		adpt_i2o_delete_hba(pHba);
		return -1;
	}

	/* In OPERATIONAL state  */
	return 0;
}