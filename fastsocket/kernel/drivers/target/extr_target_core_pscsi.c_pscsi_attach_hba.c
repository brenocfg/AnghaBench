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
struct se_hba {int /*<<< orphan*/  hba_id; struct pscsi_hba_virt* hba_ptr; } ;
struct pscsi_hba_virt {int /*<<< orphan*/  phv_mode; int /*<<< orphan*/  phv_host_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PHV_VIRTUAL_HOST_ID ; 
 int /*<<< orphan*/  PSCSI_VERSION ; 
 int /*<<< orphan*/  TARGET_CORE_MOD_VERSION ; 
 struct pscsi_hba_virt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int pscsi_attach_hba(struct se_hba *hba, u32 host_id)
{
	struct pscsi_hba_virt *phv;

	phv = kzalloc(sizeof(struct pscsi_hba_virt), GFP_KERNEL);
	if (!phv) {
		pr_err("Unable to allocate struct pscsi_hba_virt\n");
		return -ENOMEM;
	}
	phv->phv_host_id = host_id;
	phv->phv_mode = PHV_VIRTUAL_HOST_ID;

	hba->hba_ptr = phv;

	pr_debug("CORE_HBA[%d] - TCM SCSI HBA Driver %s on"
		" Generic Target Core Stack %s\n", hba->hba_id,
		PSCSI_VERSION, TARGET_CORE_MOD_VERSION);
	pr_debug("CORE_HBA[%d] - Attached SCSI HBA to Generic\n",
	       hba->hba_id);

	return 0;
}