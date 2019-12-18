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
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_vector_map_info {scalar_t__ irq; int channel_id; int phys_id; int core_id; } ;
struct TYPE_2__ {int num_online_cpu; int num_present_cpu; struct lpfc_vector_map_info* cpu_map; } ;
struct lpfc_hba {scalar_t__ sli_rev; scalar_t__ intr_type; int cfg_fcp_cpu_map; TYPE_1__ sli4_hba; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ LPFC_VECTOR_MAP_EMPTY ; 
 scalar_t__ MSIX ; 
 scalar_t__ PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,int,...) ; 

__attribute__((used)) static ssize_t
lpfc_fcp_cpu_map_show(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *)shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_vector_map_info *cpup;
	int  idx, len = 0;

	if ((phba->sli_rev != LPFC_SLI_REV4) ||
	    (phba->intr_type != MSIX))
		return len;

	switch (phba->cfg_fcp_cpu_map) {
	case 0:
		len += snprintf(buf + len, PAGE_SIZE-len,
				"fcp_cpu_map: No mapping (%d)\n",
				phba->cfg_fcp_cpu_map);
		return len;
	case 1:
		len += snprintf(buf + len, PAGE_SIZE-len,
				"fcp_cpu_map: HBA centric mapping (%d): "
				"%d online CPUs\n",
				phba->cfg_fcp_cpu_map,
				phba->sli4_hba.num_online_cpu);
		break;
	case 2:
		len += snprintf(buf + len, PAGE_SIZE-len,
				"fcp_cpu_map: Driver centric mapping (%d): "
				"%d online CPUs\n",
				phba->cfg_fcp_cpu_map,
				phba->sli4_hba.num_online_cpu);
		break;
	}

	cpup = phba->sli4_hba.cpu_map;
	for (idx = 0; idx < phba->sli4_hba.num_present_cpu; idx++) {
		if (cpup->irq == LPFC_VECTOR_MAP_EMPTY)
			len += snprintf(buf + len, PAGE_SIZE-len,
					"CPU %02d io_chan %02d "
					"physid %d coreid %d\n",
					idx, cpup->channel_id, cpup->phys_id,
					cpup->core_id);
		else
			len += snprintf(buf + len, PAGE_SIZE-len,
					"CPU %02d io_chan %02d "
					"physid %d coreid %d IRQ %d\n",
					idx, cpup->channel_id, cpup->phys_id,
					cpup->core_id, cpup->irq);

		cpup++;
	}
	return len;
}