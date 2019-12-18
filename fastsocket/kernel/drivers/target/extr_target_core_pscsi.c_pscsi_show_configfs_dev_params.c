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
struct se_device {TYPE_1__* se_hba; } ;
struct scsi_device {int* vendor; int* model; int* rev; } ;
struct pscsi_hba_virt {scalar_t__ phv_mode; } ;
struct pscsi_dev_virt {int pdv_host_id; int pdv_channel_id; int pdv_target_id; int pdv_lun_id; struct scsi_device* pdv_sd; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct pscsi_hba_virt* hba_ptr; } ;

/* Variables and functions */
 scalar_t__ ISPRINT (int) ; 
 scalar_t__ PHV_VIRTUAL_HOST_ID ; 
 struct pscsi_dev_virt* PSCSI_DEV (struct se_device*) ; 
 int /*<<< orphan*/  snprintf (unsigned char*,int,char*,...) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t pscsi_show_configfs_dev_params(struct se_device *dev, char *b)
{
	struct pscsi_hba_virt *phv = dev->se_hba->hba_ptr;
	struct pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	struct scsi_device *sd = pdv->pdv_sd;
	unsigned char host_id[16];
	ssize_t bl;
	int i;

	if (phv->phv_mode == PHV_VIRTUAL_HOST_ID)
		snprintf(host_id, 16, "%d", pdv->pdv_host_id);
	else
		snprintf(host_id, 16, "PHBA Mode");

	bl = sprintf(b, "SCSI Device Bus Location:"
		" Channel ID: %d Target ID: %d LUN: %d Host ID: %s\n",
		pdv->pdv_channel_id, pdv->pdv_target_id, pdv->pdv_lun_id,
		host_id);

	if (sd) {
		bl += sprintf(b + bl, "        ");
		bl += sprintf(b + bl, "Vendor: ");
		for (i = 0; i < 8; i++) {
			if (ISPRINT(sd->vendor[i]))   /* printable character? */
				bl += sprintf(b + bl, "%c", sd->vendor[i]);
			else
				bl += sprintf(b + bl, " ");
		}
		bl += sprintf(b + bl, " Model: ");
		for (i = 0; i < 16; i++) {
			if (ISPRINT(sd->model[i]))   /* printable character ? */
				bl += sprintf(b + bl, "%c", sd->model[i]);
			else
				bl += sprintf(b + bl, " ");
		}
		bl += sprintf(b + bl, " Rev: ");
		for (i = 0; i < 4; i++) {
			if (ISPRINT(sd->rev[i]))   /* printable character ? */
				bl += sprintf(b + bl, "%c", sd->rev[i]);
			else
				bl += sprintf(b + bl, " ");
		}
		bl += sprintf(b + bl, "\n");
	}
	return bl;
}