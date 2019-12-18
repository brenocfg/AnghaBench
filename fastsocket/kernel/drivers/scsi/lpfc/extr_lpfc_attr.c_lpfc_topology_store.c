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
typedef  int uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int cfg_topology; scalar_t__ cfg_link_speed; scalar_t__ sli_rev; int fc_topology_changed; int /*<<< orphan*/  brd_no; int /*<<< orphan*/  pport; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ LPFC_USER_LINK_SPEED_16G ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int lpfc_issue_lip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  lpfc_shost_from_vport (int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static ssize_t
lpfc_topology_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	int val = 0;
	int nolip = 0;
	const char *val_buf = buf;
	int err;
	uint32_t prev_val;

	if (!strncmp(buf, "nolip ", strlen("nolip "))) {
		nolip = 1;
		val_buf = &buf[strlen("nolip ")];
	}

	if (!isdigit(val_buf[0]))
		return -EINVAL;
	if (sscanf(val_buf, "%i", &val) != 1)
		return -EINVAL;

	if (val >= 0 && val <= 6) {
		prev_val = phba->cfg_topology;
		phba->cfg_topology = val;
		if (phba->cfg_link_speed == LPFC_USER_LINK_SPEED_16G &&
			val == 4) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"3113 Loop mode not supported at speed %d\n",
				phba->cfg_link_speed);
			phba->cfg_topology = prev_val;
			return -EINVAL;
		}
		if (nolip)
			return strlen(buf);

		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
			"3054 lpfc_topology changed from %d to %d\n",
			prev_val, val);
		if (prev_val != val && phba->sli_rev == LPFC_SLI_REV4)
			phba->fc_topology_changed = 1;
		err = lpfc_issue_lip(lpfc_shost_from_vport(phba->pport));
		if (err) {
			phba->cfg_topology = prev_val;
			return -EINVAL;
		} else
			return strlen(buf);
	}
	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
		"%d:0467 lpfc_topology attribute cannot be set to %d, "
		"allowed range is [0, 6]\n",
		phba->brd_no, val);
	return -EINVAL;
}