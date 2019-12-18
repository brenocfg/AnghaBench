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
typedef  int /*<<< orphan*/  wwnn ;
typedef  unsigned int u8 ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int /*<<< orphan*/  brd_no; TYPE_1__* pcidev; int /*<<< orphan*/  cfg_soft_wwnn; int /*<<< orphan*/  soft_wwn_enable; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wwn_to_u64 (unsigned int*) ; 

__attribute__((used)) static ssize_t
lpfc_soft_wwnn_store(struct device *dev, struct device_attribute *attr,
		     const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct lpfc_hba *phba = ((struct lpfc_vport *)shost->hostdata)->phba;
	unsigned int i, j, cnt=count;
	u8 wwnn[8];

	/* count may include a LF at end of string */
	if (buf[cnt-1] == '\n')
		cnt--;

	if (!phba->soft_wwn_enable || (cnt < 16) || (cnt > 18) ||
	    ((cnt == 17) && (*buf++ != 'x')) ||
	    ((cnt == 18) && ((*buf++ != '0') || (*buf++ != 'x'))))
		return -EINVAL;

	/*
	 * Allow wwnn to be set many times, as long as the enable is set.
	 * However, once the wwpn is set, everything locks.
	 */

	memset(wwnn, 0, sizeof(wwnn));

	/* Validate and store the new name */
	for (i=0, j=0; i < 16; i++) {
		if ((*buf >= 'a') && (*buf <= 'f'))
			j = ((j << 4) | ((*buf++ -'a') + 10));
		else if ((*buf >= 'A') && (*buf <= 'F'))
			j = ((j << 4) | ((*buf++ -'A') + 10));
		else if ((*buf >= '0') && (*buf <= '9'))
			j = ((j << 4) | (*buf++ -'0'));
		else
			return -EINVAL;
		if (i % 2) {
			wwnn[i/2] = j & 0xff;
			j = 0;
		}
	}
	phba->cfg_soft_wwnn = wwn_to_u64(wwnn);

	dev_printk(KERN_NOTICE, &phba->pcidev->dev,
		   "lpfc%d: soft_wwnn set. Value will take effect upon "
		   "setting of the soft_wwpn\n", phba->brd_no);

	return count;
}