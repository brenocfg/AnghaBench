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
struct lpfc_hba {scalar_t__ sli_rev; int cfg_poll; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  HCregaddr; int /*<<< orphan*/  fcp_poll_timer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DISABLE_FCP_RING_INT ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENABLE_FCP_RING_POLLING ; 
 int HC_R0INT_ENA ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_FCP_RING ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  lpfc_poll_start_timer (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ lpfc_readl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
lpfc_poll_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	uint32_t creg_val;
	uint32_t old_val;
	int val=0;

	if (!isdigit(buf[0]))
		return -EINVAL;

	if (sscanf(buf, "%i", &val) != 1)
		return -EINVAL;

	if ((val & 0x3) != val)
		return -EINVAL;

	if (phba->sli_rev == LPFC_SLI_REV4)
		val = 0;

	lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
		"3051 lpfc_poll changed from %d to %d\n",
		phba->cfg_poll, val);

	spin_lock_irq(&phba->hbalock);

	old_val = phba->cfg_poll;

	if (val & ENABLE_FCP_RING_POLLING) {
		if ((val & DISABLE_FCP_RING_INT) &&
		    !(old_val & DISABLE_FCP_RING_INT)) {
			if (lpfc_readl(phba->HCregaddr, &creg_val)) {
				spin_unlock_irq(&phba->hbalock);
				return -EINVAL;
			}
			creg_val &= ~(HC_R0INT_ENA << LPFC_FCP_RING);
			writel(creg_val, phba->HCregaddr);
			readl(phba->HCregaddr); /* flush */

			lpfc_poll_start_timer(phba);
		}
	} else if (val != 0x0) {
		spin_unlock_irq(&phba->hbalock);
		return -EINVAL;
	}

	if (!(val & DISABLE_FCP_RING_INT) &&
	    (old_val & DISABLE_FCP_RING_INT))
	{
		spin_unlock_irq(&phba->hbalock);
		del_timer(&phba->fcp_poll_timer);
		spin_lock_irq(&phba->hbalock);
		if (lpfc_readl(phba->HCregaddr, &creg_val)) {
			spin_unlock_irq(&phba->hbalock);
			return -EINVAL;
		}
		creg_val |= (HC_R0INT_ENA << LPFC_FCP_RING);
		writel(creg_val, phba->HCregaddr);
		readl(phba->HCregaddr); /* flush */
	}

	phba->cfg_poll = val;

	spin_unlock_irq(&phba->hbalock);

	return strlen(buf);
}