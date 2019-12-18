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
struct beiscsi_hba {int /*<<< orphan*/  eh_sgl_hndl_base; int /*<<< orphan*/  io_sgl_hndl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int beiscsi_init_controller (struct beiscsi_hba*) ; 
 int beiscsi_init_sgl_handle (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hba_setup_cid_tbls (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  hwi_cleanup (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beiscsi_init_port(struct beiscsi_hba *phba)
{
	int ret;

	ret = beiscsi_init_controller(phba);
	if (ret < 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : beiscsi_dev_probe - Failed in"
			    "beiscsi_init_controller\n");
		return ret;
	}
	ret = beiscsi_init_sgl_handle(phba);
	if (ret < 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : beiscsi_dev_probe - Failed in"
			    "beiscsi_init_sgl_handle\n");
		goto do_cleanup_ctrlr;
	}

	if (hba_setup_cid_tbls(phba)) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Failed in hba_setup_cid_tbls\n");
		kfree(phba->io_sgl_hndl_base);
		kfree(phba->eh_sgl_hndl_base);
		goto do_cleanup_ctrlr;
	}

	return ret;

do_cleanup_ctrlr:
	hwi_cleanup(phba);
	return ret;
}