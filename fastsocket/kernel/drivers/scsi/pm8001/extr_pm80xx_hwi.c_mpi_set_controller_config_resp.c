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
typedef  int /*<<< orphan*/  u32 ;
struct set_ctrl_cfg_resp {int /*<<< orphan*/  err_qlfr_pgcd; int /*<<< orphan*/  status; } ;
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpi_set_controller_config_resp(struct pm8001_hba_info *pm8001_ha,
			void *piomb)
{
	struct set_ctrl_cfg_resp *pPayload =
			(struct set_ctrl_cfg_resp *)(piomb + 4);
	u32 status = le32_to_cpu(pPayload->status);
	u32 err_qlfr_pgcd = le32_to_cpu(pPayload->err_qlfr_pgcd);

	PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
			"SET CONTROLLER RESP: status 0x%x qlfr_pgcd 0x%x\n",
			status, err_qlfr_pgcd));

	return 0;
}