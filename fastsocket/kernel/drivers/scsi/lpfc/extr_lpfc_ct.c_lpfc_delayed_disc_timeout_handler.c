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
struct lpfc_vport {int fc_flag; int /*<<< orphan*/  phba; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int FC_DISC_DELAYED ; 
 int /*<<< orphan*/  lpfc_do_scr_ns_plogi (int /*<<< orphan*/ ,struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_delayed_disc_timeout_handler(struct lpfc_vport *vport)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	spin_lock_irq(shost->host_lock);
	if (!(vport->fc_flag & FC_DISC_DELAYED)) {
		spin_unlock_irq(shost->host_lock);
		return;
	}
	vport->fc_flag &= ~FC_DISC_DELAYED;
	spin_unlock_irq(shost->host_lock);

	lpfc_do_scr_ns_plogi(vport->phba, vport);
}