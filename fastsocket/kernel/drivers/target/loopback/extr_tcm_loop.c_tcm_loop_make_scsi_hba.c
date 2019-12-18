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
struct se_wwn {int dummy; } ;
struct tcm_loop_hba {struct se_wwn tl_hba_wwn; struct Scsi_Host* sh; int /*<<< orphan*/ * tl_wwn_address; int /*<<< orphan*/  tl_proto_id; } ;
struct target_fabric_configfs {int dummy; } ;
struct config_group {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct se_wwn* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCSI_PROTOCOL_FCP ; 
 int /*<<< orphan*/  SCSI_PROTOCOL_ISCSI ; 
 int /*<<< orphan*/  SCSI_PROTOCOL_SAS ; 
 scalar_t__ TL_WWN_ADDR_LEN ; 
 int /*<<< orphan*/  kfree (struct tcm_loop_hba*) ; 
 struct tcm_loop_hba* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,scalar_t__,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/  tcm_loop_dump_proto_id (struct tcm_loop_hba*) ; 
 int /*<<< orphan*/  tcm_loop_hba_no_cnt ; 
 int tcm_loop_setup_hba_bus (struct tcm_loop_hba*,int /*<<< orphan*/ ) ; 

struct se_wwn *tcm_loop_make_scsi_hba(
	struct target_fabric_configfs *tf,
	struct config_group *group,
	const char *name)
{
	struct tcm_loop_hba *tl_hba;
	struct Scsi_Host *sh;
	char *ptr;
	int ret, off = 0;

	tl_hba = kzalloc(sizeof(struct tcm_loop_hba), GFP_KERNEL);
	if (!tl_hba) {
		pr_err("Unable to allocate struct tcm_loop_hba\n");
		return ERR_PTR(-ENOMEM);
	}
	/*
	 * Determine the emulated Protocol Identifier and Target Port Name
	 * based on the incoming configfs directory name.
	 */
	ptr = strstr(name, "naa.");
	if (ptr) {
		tl_hba->tl_proto_id = SCSI_PROTOCOL_SAS;
		goto check_len;
	}
	ptr = strstr(name, "fc.");
	if (ptr) {
		tl_hba->tl_proto_id = SCSI_PROTOCOL_FCP;
		off = 3; /* Skip over "fc." */
		goto check_len;
	}
	ptr = strstr(name, "iqn.");
	if (!ptr) {
		pr_err("Unable to locate prefix for emulated Target "
				"Port: %s\n", name);
		ret = -EINVAL;
		goto out;
	}
	tl_hba->tl_proto_id = SCSI_PROTOCOL_ISCSI;

check_len:
	if (strlen(name) >= TL_WWN_ADDR_LEN) {
		pr_err("Emulated NAA %s Address: %s, exceeds"
			" max: %d\n", name, tcm_loop_dump_proto_id(tl_hba),
			TL_WWN_ADDR_LEN);
		ret = -EINVAL;
		goto out;
	}
	snprintf(&tl_hba->tl_wwn_address[0], TL_WWN_ADDR_LEN, "%s", &name[off]);

	/*
	 * Call device_register(tl_hba->dev) to register the emulated
	 * Linux/SCSI LLD of type struct Scsi_Host at tl_hba->sh after
	 * device_register() callbacks in tcm_loop_driver_probe()
	 */
	ret = tcm_loop_setup_hba_bus(tl_hba, tcm_loop_hba_no_cnt);
	if (ret)
		goto out;

	sh = tl_hba->sh;
	tcm_loop_hba_no_cnt++;
	pr_debug("TCM_Loop_ConfigFS: Allocated emulated Target"
		" %s Address: %s at Linux/SCSI Host ID: %d\n",
		tcm_loop_dump_proto_id(tl_hba), name, sh->host_no);

	return &tl_hba->tl_hba_wwn;
out:
	kfree(tl_hba);
	return ERR_PTR(ret);
}