#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct Scsi_Host* shost; } ;
struct sas_ha_struct {int num_phys; int lldd_max_execute_num; TYPE_3__ core; int /*<<< orphan*/  lldd_queue_size; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  lldd_module; int /*<<< orphan*/  dev; int /*<<< orphan*/  sas_ha_name; int /*<<< orphan*/ ** sas_port; int /*<<< orphan*/ ** sas_phy; struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  dev; TYPE_2__* port; TYPE_1__* phy; } ;
struct pm8001_chip_info {int n_phy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sas_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  sas_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  PM8001_CAN_QUEUE ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 

__attribute__((used)) static void  pm8001_post_sas_ha_init(struct Scsi_Host *shost,
				     const struct pm8001_chip_info *chip_info)
{
	int i = 0;
	struct pm8001_hba_info *pm8001_ha;
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);

	pm8001_ha = sha->lldd_ha;
	for (i = 0; i < chip_info->n_phy; i++) {
		sha->sas_phy[i] = &pm8001_ha->phy[i].sas_phy;
		sha->sas_port[i] = &pm8001_ha->port[i].sas_port;
	}
	sha->sas_ha_name = DRV_NAME;
	sha->dev = pm8001_ha->dev;

	sha->lldd_module = THIS_MODULE;
	sha->sas_addr = &pm8001_ha->sas_addr[0];
	sha->num_phys = chip_info->n_phy;
	sha->lldd_max_execute_num = 1;
	sha->lldd_queue_size = PM8001_CAN_QUEUE;
	sha->core.shost = shost;
}