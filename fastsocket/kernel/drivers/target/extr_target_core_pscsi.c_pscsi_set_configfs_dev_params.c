#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  substring_t ;
struct se_device {TYPE_1__* se_hba; } ;
struct pscsi_hba_virt {int /*<<< orphan*/  phv_host_id; int /*<<< orphan*/  phv_mode; } ;
struct pscsi_dev_virt {int pdv_host_id; int pdv_channel_id; int pdv_target_id; int pdv_lun_id; int /*<<< orphan*/  pdv_flags; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct pscsi_hba_virt* hba_ptr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_scsi_channel_id 131 
#define  Opt_scsi_host_id 130 
#define  Opt_scsi_lun_id 129 
#define  Opt_scsi_target_id 128 
 int /*<<< orphan*/  PDF_HAS_CHANNEL_ID ; 
 int /*<<< orphan*/  PDF_HAS_LUN_ID ; 
 int /*<<< orphan*/  PDF_HAS_TARGET_ID ; 
 int /*<<< orphan*/  PDF_HAS_VIRT_HOST_ID ; 
 int /*<<< orphan*/  PHV_LLD_SCSI_HOST_NO ; 
 struct pscsi_dev_virt* PSCSI_DEV (struct se_device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static ssize_t pscsi_set_configfs_dev_params(struct se_device *dev,
		const char *page, ssize_t count)
{
	struct pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	struct pscsi_hba_virt *phv = dev->se_hba->hba_ptr;
	char *orig, *ptr, *opts;
	substring_t args[MAX_OPT_ARGS];
	int ret = 0, arg, token;

	opts = kstrdup(page, GFP_KERNEL);
	if (!opts)
		return -ENOMEM;

	orig = opts;

	while ((ptr = strsep(&opts, ",\n")) != NULL) {
		if (!*ptr)
			continue;

		token = match_token(ptr, tokens, args);
		switch (token) {
		case Opt_scsi_host_id:
			if (phv->phv_mode == PHV_LLD_SCSI_HOST_NO) {
				pr_err("PSCSI[%d]: Unable to accept"
					" scsi_host_id while phv_mode =="
					" PHV_LLD_SCSI_HOST_NO\n",
					phv->phv_host_id);
				ret = -EINVAL;
				goto out;
			}
			match_int(args, &arg);
			pdv->pdv_host_id = arg;
			pr_debug("PSCSI[%d]: Referencing SCSI Host ID:"
				" %d\n", phv->phv_host_id, pdv->pdv_host_id);
			pdv->pdv_flags |= PDF_HAS_VIRT_HOST_ID;
			break;
		case Opt_scsi_channel_id:
			match_int(args, &arg);
			pdv->pdv_channel_id = arg;
			pr_debug("PSCSI[%d]: Referencing SCSI Channel"
				" ID: %d\n",  phv->phv_host_id,
				pdv->pdv_channel_id);
			pdv->pdv_flags |= PDF_HAS_CHANNEL_ID;
			break;
		case Opt_scsi_target_id:
			match_int(args, &arg);
			pdv->pdv_target_id = arg;
			pr_debug("PSCSI[%d]: Referencing SCSI Target"
				" ID: %d\n", phv->phv_host_id,
				pdv->pdv_target_id);
			pdv->pdv_flags |= PDF_HAS_TARGET_ID;
			break;
		case Opt_scsi_lun_id:
			match_int(args, &arg);
			pdv->pdv_lun_id = arg;
			pr_debug("PSCSI[%d]: Referencing SCSI LUN ID:"
				" %d\n", phv->phv_host_id, pdv->pdv_lun_id);
			pdv->pdv_flags |= PDF_HAS_LUN_ID;
			break;
		default:
			break;
		}
	}

out:
	kfree(orig);
	return (!ret) ? count : ret;
}