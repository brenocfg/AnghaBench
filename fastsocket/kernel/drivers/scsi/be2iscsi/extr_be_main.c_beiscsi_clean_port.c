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
struct beiscsi_hba {int /*<<< orphan*/  conn_table; int /*<<< orphan*/  ep_array; int /*<<< orphan*/  cid_array; int /*<<< orphan*/  eh_sgl_hndl_base; int /*<<< orphan*/  io_sgl_hndl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  CMD_CONNECTION_CHUTE_0 ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hwi_cleanup (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  hwi_purge_eq (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int mgmt_epfw_cleanup (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void beiscsi_clean_port(struct beiscsi_hba *phba)
{
	int mgmt_status;

	mgmt_status = mgmt_epfw_cleanup(phba, CMD_CONNECTION_CHUTE_0);
	if (mgmt_status)
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : mgmt_epfw_cleanup FAILED\n");

	hwi_purge_eq(phba);
	hwi_cleanup(phba);
	kfree(phba->io_sgl_hndl_base);
	kfree(phba->eh_sgl_hndl_base);
	kfree(phba->cid_array);
	kfree(phba->ep_array);
	kfree(phba->conn_table);
}