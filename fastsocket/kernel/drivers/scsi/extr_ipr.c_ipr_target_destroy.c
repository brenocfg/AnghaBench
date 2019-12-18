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
struct scsi_target {scalar_t__ channel; struct ipr_sata_port* hostdata; int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;
struct ipr_sata_port {int /*<<< orphan*/  ap; } ;
struct ipr_ioa_cfg {int /*<<< orphan*/  target_ids; int /*<<< orphan*/  vset_ids; int /*<<< orphan*/  array_ids; scalar_t__ sis64; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 scalar_t__ IPR_ARRAY_VIRTUAL_BUS ; 
 scalar_t__ IPR_VSET_VIRTUAL_BUS ; 
 int /*<<< orphan*/  ata_sas_port_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipr_find_starget (struct scsi_target*) ; 
 int /*<<< orphan*/  kfree (struct ipr_sata_port*) ; 

__attribute__((used)) static void ipr_target_destroy(struct scsi_target *starget)
{
	struct ipr_sata_port *sata_port = starget->hostdata;
	struct Scsi_Host *shost = dev_to_shost(&starget->dev);
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *) shost->hostdata;

	if (ioa_cfg->sis64) {
		if (!ipr_find_starget(starget)) {
			if (starget->channel == IPR_ARRAY_VIRTUAL_BUS)
				clear_bit(starget->id, ioa_cfg->array_ids);
			else if (starget->channel == IPR_VSET_VIRTUAL_BUS)
				clear_bit(starget->id, ioa_cfg->vset_ids);
			else if (starget->channel == 0)
				clear_bit(starget->id, ioa_cfg->target_ids);
		}
	}

	if (sata_port) {
		starget->hostdata = NULL;
		ata_sas_port_destroy(sata_port->ap);
		kfree(sata_port);
	}
}